#pragma once
#include <string_view>
#include <vector>

namespace ecs {
    struct ComponentQuery {
        std::string_view name;
        bool mut;
    };

    class QueryDefinition {
    public:
        std::vector<ComponentQuery> component;
    };
}
