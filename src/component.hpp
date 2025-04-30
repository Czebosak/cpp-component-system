#pragma once
#include <unordered_set>
#include <typeinfo>

#include <string_name.hpp>
#include <event.hpp>

class Entity;

class Component {
protected:
    mutable std::optional<StringName> name;
public:
    const StringName& get_name() const {
        if (!name.has_value()) {
            name = std::make_optional(StringName(typeid(*this).name()));
        }
        return *name;
    }

    virtual void added_to_entity(Entity& entity) {}

    virtual void process(Entity& entity) {}
};
