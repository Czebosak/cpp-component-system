#include <string_name.hpp>
#include <iostream>

std::unordered_map<std::string, size_t> StringName::database;

StringName::StringName(const std::string& str) {
    auto it = database.find(str);
    if (it != database.end()) {
        interned_string = it->first;
        hash = it->second;
    } else {
        auto [it, success] = database.emplace(str, std::hash<std::string>{}(str)); 
        interned_string = it->first;
        hash = it->second;
    }
}

StringName::StringName(const char* str) : StringName(std::string(str)) {}
