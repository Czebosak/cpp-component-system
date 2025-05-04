#pragma once
#include <vector>
#include <memory>

#include <system_definition.hpp>
#include <entity.hpp>

class World {
private:
    std::vector<Entity> entities;
    std::vector<ecs::System> systems;
public:
    void process();

    Entity& add_entity(Entity entity) {
        return entities.emplace_back(std::move(entity));
    }

    template<typename ComponentType, typename... Args>
    Entity& add_entity_with_component(Args&&... args) {
        static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component");

        Entity& entity = entities.emplace_back();
        entity.add_component<ComponentType>(std::forward<Args>(args)...);
        return entity;
    }

    Entity& add_entity_with_components(std::vector<std::unique_ptr<Component>>&& components, Entity::ProcessMode process_mode = Entity::ProcessMode::ALWAYS) {
        Entity& entity = entities.emplace_back(process_mode);
        entity.add_components(std::move(components));
        return entity;
    }
};
