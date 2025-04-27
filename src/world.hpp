#pragma once
#include <vector>
#include <memory>

#include <entity.hpp>

class World {
private:
    std::vector<Entity> entities;
public:
    void process();

    void add_entity(Entity entity) {
        entities.emplace_back(std::move(entity));
    }

    void add_entity_with_components(std::vector<std::unique_ptr<Component>>&& components, Entity::ProcessMode process_mode = Entity::ProcessMode::ALWAYS) {
        entities.emplace_back(std::move(components), process_mode);
    }
};
