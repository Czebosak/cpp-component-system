#pragma once
#include <functional>
#include <unordered_map>

#include <string_name.hpp>

#include <component.hpp>

#define BIND_EVENT_CALLBACK(callback) this, [this](auto&&... args) { this->callback(std::forward<decltype(args)>(args)...); }

template<typename... Args>
class Event {
public:
    using Callback = std::function<void(Args...)>;
private:
    std::unordered_map<Component*, Callback> listeners;
public:

    void subscribe(Component* listener, const Callback& callback) {
        listeners.emplace(listener, callback);
    }

    void unsubscribe(Component* listener) {
        listeners.erase(listener);
    }

    void trigger(Args... args) {
        for (auto& [listener, callback] : listeners) {
            callback(args...);
        }
    }
};
