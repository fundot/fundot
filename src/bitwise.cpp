#include "fundot/fundot.h"

namespace fundot {

Object operator&(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         & std::any_cast<const Integer&>(rhs.value).value})};
    }
    throw std::runtime_error("Invalid operand type.");
}

Object operator|(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         | std::any_cast<const Integer&>(rhs.value).value})};
    }
    throw std::runtime_error("Invalid operand type.");
}

Object operator^(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         ^ std::any_cast<const Integer&>(rhs.value).value})};
    }
    throw std::runtime_error("Invalid operand type.");
}

Object operator~(const Object& object)
{
    if (object.value.type() == typeid(Integer)) {
        return {Integer({~std::any_cast<const Integer&>(object.value).value})};
    }
    throw std::runtime_error("Invalid operand type.");
}

Object operator<<(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         << std::any_cast<const Integer&>(rhs.value).value})};
    }
    throw std::runtime_error("Invalid operand type.");
}

Object operator>>(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         >> std::any_cast<const Integer&>(rhs.value).value})};
    }
    throw std::runtime_error("Invalid operand type.");
}

}  // namespace fundot
