#pragma once
#include <functional>
#include <unordered_map>

#include <string_name.hpp>

class Component;

#define BIND_EVENT_CALLBACK(callback) this, [this](auto&&... args) { this->callback(std::forward<decltype(args)>(args)...); }
#define EVENT_SUBSCRIBE(event, callback) event.subscribe(BIND_EVENT_CALLBACK(callback)); register_event(event)

template<typename... Args>
class Event {
public:
    using Callback = std::function<void(Args...)>;
private:
    std::unordered_multimap<Component*, Callback> listeners;
public:
    void subscribe(Component* listener, const Callback& callback) {
        listeners.emplace(listener, callback);
    }

    void unsubscribe(Component* listener, const Callback& callback) {
        // Traverse the values to find the right callback
        auto range = listeners.equal_range(listener);
        for (auto it = range.first; it != range.second; ++it) {
            auto& current_callback = it->second;
            if (callback == current_callback) {
                listeners.erase(it);
                break;
            }
        }
    }

    void unsubscribe_component(Component* listener) {
        listeners.erase(listener);
    }

    void trigger(Args... args) {
        for (auto& [listener, callback] : listeners) {
            callback(args...);
        }
    }
};
