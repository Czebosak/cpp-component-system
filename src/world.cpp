#include "world.hpp"

void World::process() {
    for (auto& system : systems) {
        system.function();
    }
}
