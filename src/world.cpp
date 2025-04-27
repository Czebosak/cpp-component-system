#include "world.hpp"

void World::process() {
    for (auto& entity : entities) {
        switch (entity.process_mode) {
            case Entity::ProcessMode::ALWAYS:
                entity.process();
                break;
        }
    }
}
