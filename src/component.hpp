#pragma once
#include <unordered_set>
#include <typeinfo>
#include <optional>
#include <vector>
#include <functional>

#include <string_name.hpp>
#include <event.hpp>

class Entity;

class Component {
private:
    mutable std::optional<StringName> name;
    std::vector<std::function<void()>> unsubscribe_functions;
protected:
    template <typename... Args>
    void register_event(Event<Args...>& event) {
        unsubscribe_functions.emplace_back([this, &event]() { event.unsubscribe_component(this); });
    }
public:
    virtual ~Component() {
        for (auto& unsubscribe_function : unsubscribe_functions) {
            unsubscribe_function();
        }
    }

    const StringName& get_name() const {
        if (!name.has_value()) {
            name = std::make_optional(StringName(typeid(*this).name()));
        }
        return *name;
    }

    virtual void added_to_entity(Entity& entity) {}

    virtual void process(Entity& entity) {}
};
