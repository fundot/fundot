#include "number.h"
#include <functional>

namespace fundot {

int Number::int_value() const {
    std::string message{'\''};
    message += typeid(*this).name();
    message += '\'';
    message += " cannot be converted to an 'int'";
    throw Error{message};
}

double Number::double_value() const {
    std::string message{'\''};
    message += typeid(*this).name();
    message += '\'';
    message += " cannot be converted to a 'double'";
    throw Error{message};
}

Integer::Integer(std::int64_t raw_int) : raw_int{raw_int} {
}

bool Integer::equals(const Object* obj) const {
    auto other{dynamic_cast<const Integer*>(obj)};
    return other != nullptr && raw_int == other->raw_int;
}

std::size_t Integer::hash() const {
    return std::hash<std::int64_t>{}(raw_int);
}

std::string Integer::to_string() const {
    return std::to_string(raw_int);
}

int Integer::int_value() const {
    return raw_int;
}

double Integer::double_value() const {
    return raw_int;
}

Float::Float(double raw_float) : raw_float{raw_float} {
}

bool Float::equals(const Object* obj) const {
    auto other{dynamic_cast<const Float*>(obj)};
    return other != nullptr && raw_float == other->raw_float;
}

std::size_t Float::hash() const {
    return std::hash<double>{}(raw_float);
}

std::string Float::to_string() const {
    return std::to_string(raw_float);
}

int Float::int_value() const {
    return raw_float;
}

double Float::double_value() const {
    return raw_float;
}

}
