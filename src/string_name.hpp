#pragma once
#include <string_view>
#include <unordered_map>
#include <functional>
#include <utils.hpp>

class StringName {
private:
    static std::unordered_map<std::string, size_t> database;
    std::string_view interned_string;
    size_t hash;
public:
    StringName(const std::string& str);

    StringName(const char* str);

    bool operator==(const StringName& other) const {
        return interned_string == other.interned_string;
    }

    /* bool operator==(const std::string& other) const {
        return interned_string == other;
    } */

    const std::string_view get_string_view() const {
        return interned_string;
    }

    size_t get_hash() const {
        return hash;
    }
};

namespace std {
    template <>
    struct hash<StringName> {
        size_t operator()(const StringName& s) const {
            return s.get_hash();
        }
    };
}
