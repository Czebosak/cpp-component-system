#include "entity.hpp"

void Entity::process() {
    for (auto&& [_, component] : components) {
        component->process(*this);
    }
}