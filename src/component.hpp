#pragma once
#include <string_name.hpp>
#include <typeinfo>

class Entity;

class Component {
protected:
    mutable std::optional<StringName> name;
public: 
    virtual ~Component() = default;

    const StringName& get_name() const {
        if (!name.has_value()) {
            name = std::make_optional(StringName(typeid(*this).name()));
        }
        return *name;
    }

    virtual void added_to_entity(Entity& entity) {}

    virtual void process(Entity& entity) {}
};
