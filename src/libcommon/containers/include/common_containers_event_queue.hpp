#ifndef LIBCOMMON_CONTAINERS_INCLUDE_COMMON_CONTAINERS_EVENT_QUEUE_HPP
#define LIBCOMMON_CONTAINERS_INCLUDE_COMMON_CONTAINERS_EVENT_QUEUE_HPP

#include "common_containers_stdlib.hpp"
#include <functional>
#include <type_traits>

namespace common::containers {
template <class Event, class T>
class event_queue {
    using subscribe_function = std::function<void(const Event &, const T &)>;

public:
    template <class... Args,
              class = std::void_t<std::enable_if_t<std::is_convertible_v<Args, Event>>...>>
    explicit event_queue(Args &&... args);

    void push(const Event & event, const T & t);
    void subscribe(subscribe_function f);
    void update();

private:
    stdlib::vector<subscribe_function> _subscribers;
    stdlib::vector<Event>              _whitelist;
    stdlib::queue<std::pair<Event, T>> _queue;
};
} // namespace common::containers

#include "../common_containers_event_queue.tpp"

#endif
