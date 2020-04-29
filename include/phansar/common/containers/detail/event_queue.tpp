#include <phansar/common/containers/event_queue.hpp>

#include <phansar/vendor/rangev3.hpp>

namespace phansar::common::containers {
template <class Event, class T>
template <class... Args, class>
event_queue<Event, T>::event_queue(Args &&... args) : _whitelist{std::forward<Args>(args)...} {}

template <class Event, class T>
void event_queue<Event, T>::push(const Event & event, const T & t) {
    if (! _whitelist.empty() &&
        ranges::none_of(_whitelist, [&event](const auto & w) { return w == event; })) {
        return;
    }

    _queue.emplace(std::make_pair(event, t));
}

template <class Event, class T>
void event_queue<Event, T>::subscribe(subscribe_function f) {
    _subscribers.emplace_back(std::move(f));
}

template <class Event, class T>
void event_queue<Event, T>::update() {
    while (! _queue.empty()) {
        ranges::for_each(_subscribers, [this](const auto & s) { std::apply(s, _queue.front()); });

        _queue.pop();
    }
}
} // namespace phansar::common::containers
