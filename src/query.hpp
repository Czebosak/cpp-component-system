#pragma once
#include <world.hpp>

template <typename... Args>
class Query {
private:
    World& world;
public:
    Query(World& world) : world(world) {}

    void get();
};
