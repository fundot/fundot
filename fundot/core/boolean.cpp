#include "boolean.h"

namespace fundot {

Boolean::Boolean(bool raw_bool) : raw_bool(raw_bool) {
}

bool Boolean::equals(const Object* obj) const {
    auto other{dynamic_cast<const Boolean*>(obj)};
    return other != nullptr && raw_bool == other->raw_bool;
}

std::size_t Boolean::hash() const {
    return std::hash<bool>{}(raw_bool);
}

std::string Boolean::to_string() const {
    return raw_bool ? "true" : "false";
}

bool Boolean::bool_value() const {
    return raw_bool;
}

}
