#pragma once
#include <vector>
#include <string_view>
#include <functional>

#include <query_definition.hpp>

namespace ecs {
    struct System {
        std::function<void()> function;
        std::vector<QueryDefinition> queries;
    };
}
