#include "common_containers_event_queue.hpp"

namespace common::containers {
template <class Event, class T>
template <class... Args, class>
event_queue<Event, T>::event_queue(Args &&... args) : _whitelist{std::forward<Args>(args)...} {
}

template <class Event, class T>
void event_queue<Event, T>::push(const Event &event, const T &t) {
    if (! _whitelist.empty()) {
        auto found = bool{false};
        for (const auto &w : _whitelist) {
            if (w == event) {
                found = true;
            }
        }

        if (! found) {
            return;
        }
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
        auto &[event, t] = _queue.front();
        _queue.pop();

        for (const auto &s : _subscribers) {
            s(event, t);
        }
    }
}
} // namespace common::containers
