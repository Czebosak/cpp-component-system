#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <cstring>

#include <query.hpp>
#include <query_definition.hpp>

#define STRING_SPLIT_BY_PATTERN(str, delimiter) \
    std::vector<std::string_view> result; \
    { \
        size_t start = 0; \
        \
        while (true) { \
            size_t pos = str.find(delimiter, start); \
            if (pos == std::string_view::npos) { \
                result.emplace_back(str.substr(start)); \
                break; \
            } \
            result.emplace_back(str.substr(start, pos - start)); \
            start = pos + strlen(delimiter); \
        } \
    }

#define SYSTEM_DEFINE(system_name, ...) \
    inline constexpr auto SYSTEM_##system_name##_VARIABLES = []() { \
        constexpr std::array<ecs::QueryDefinition, 1> processed_args; \
        \
        constexpr std::string_view args = #__VA_ARGS__; \
        STRING_SPLIT_BY_PATTERN(args, ", ") \
        std::vector<std::string_view> split_args = result; \
        for (size_t i = 0; i < split_args.size(); i++) { \
            const std::string_view& arg = split_args[i]; \
            ecs::QueryDefinition processed_arg; \
            ecs::ComponentQuery component_query; \
            \
            component_query.mut = !arg.starts_with("const"); \
            \
            size_t start_pos = arg.find('<'); \
            size_t end_pos = arg.find('>', start_pos); \
            const std::string_view& query_args = std::string_view(arg).substr(start_pos + 1, end_pos - start_pos - 1); \
            \
            component_query.name = query_args; \
            \
            processed_arg.component.emplace_back(component_query); \
            \
            processed_args[i] = processed_arg; \
        } \
        \
        return processed_args; \
    }(); \
    void system_name(__VA_ARGS__)

#define SYSTEM_REGISTER(world, name) \
    { \
        constexpr std::function<void()> system_fn = std::bind(name, SYSTEM_##name##_VARIABLES); \
        ##name##; \
    }
