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
    auto scope{get_scope()};
    while (!Object::Equal{}(scope, new Null)) {
        try {
            return scope->get(this);
        } catch (...) {
            scope = scope->get(new Symbol{"__parent_scope__"});
        }
    }
    throw Error{"symbol '" + to_string() + "' not defined"};
}

const std::string& Symbol::string_value() const {
    return raw_str;
}

}
