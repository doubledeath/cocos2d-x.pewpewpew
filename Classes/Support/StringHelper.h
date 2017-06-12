#pragma once

#include <string>
#include <sstream>

class StringHelper {
public:
    template<typename T>
    static std::string to_string(T Target);
};

template<typename T>
std::string StringHelper::to_string(T Target) {
    std::ostringstream Stream;

    Stream << Target;

    return Stream.str();
}
