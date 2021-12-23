#include "symbol.h"
#include <functional>

namespace fundot {

Symbol::Symbol(const std::string& raw_str) : raw_str{raw_str} {
}

bool Symbol::equals(const Object* obj) const {
    auto other{dynamic_cast<const Symbol*>(obj)};
    return other != nullptr && raw_str == other->raw_str;
}

std::size_t Symbol::hash() const {
    return std::hash<std::string>{}(raw_str);
}

std::string Symbol::to_string() const {
    return raw_str;
}

Object* Symbol::eval() {
    try {
        return get_scope()->get(this);
    } catch (Error& error) {
        throw Error{"symbol '" + to_string() + "' not defined"};
    }
}

}
