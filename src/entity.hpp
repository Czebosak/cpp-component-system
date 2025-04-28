#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <span>
#include <optional>
#include <iostream>

#include <optional_ref.hpp>
#include <component.hpp>

class Entity {
private:
    std::unordered_map<StringName, std::unique_ptr<Component>> components;
public:
    enum __attribute__ ((__packed__)) ProcessMode {
        ALWAYS,
        NEVER,
        ON_CONDITION
    };

    Entity(ProcessMode process_mode = ProcessMode::ALWAYS) : process_mode(process_mode) {}

    ProcessMode process_mode;

    void process();

    template <typename T>
    OptionalRef<T> get_component_safe() {
        auto it = components.find(typeid(T).name());
        if (it != components.end()) {
            auto* component = &(*it->second);
            auto* casted_component = dynamic_cast<T*>(component);
            return std::make_optional<std::reference_wrapper<T>>(*casted_component);  
        } else {
            return std::nullopt;
        }
    }

    template <typename T>
    T& get_component() {
        auto component_opt = get_component_safe<T>();

        if (auto component = component_opt) {
            return *component;
        } else {
            std::cout << std::format("Component {} not found", std::string(typeid(T).name())) << std::endl;
            abort();
        }
    }

    void add_component(std::unique_ptr<Component> component) {
        this->components.emplace(component->get_name(), std::move(component));
    }

    template<typename ComponentType, typename... Args>
    void add_component(Args&&... args) {
        static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component");

        this->components.emplace(StringName(typeid(ComponentType).name()), std::make_unique<ComponentType>(std::forward<Args>(args)...));
    }

    void add_components(std::vector<std::unique_ptr<Component>>&& components) {
        this->components.reserve(components.size());

        for (auto&& component : components) {
            this->components.emplace(component->get_name(), std::move(component));
        }
    }
};
