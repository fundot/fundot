#include "string.h"
#include <functional>

namespace fundot {

String::String(const std::string& raw_str) : raw_str{raw_str} {
}

bool String::equals(const Object* obj) const {
    auto other{dynamic_cast<const String*>(obj)};
    return other != nullptr && raw_str == other->raw_str;
}

std::size_t String::hash() const {
    return std::hash<std::string>{}(raw_str);
}

std::string String::to_string() const {
    return '"' + raw_str + '"';
}

bool String::equals(const std::string& other) const {
    return raw_str == other;
}

}
