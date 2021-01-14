#include "fundot_type.h"

namespace fundot {

template<class T>
bool compare(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Setter)) {
        return T{}(std::any_cast<const Setter&>(lhs.value).value.first, rhs);
    }
    if (rhs.value.type() == typeid(Setter)) {
        return T{}(lhs, std::any_cast<const Setter&>(rhs.value).value.first);
    }
    if (lhs.value.type() == rhs.value.type()) {
        if (lhs.value.type() == typeid(Boolean)) {
            return T{}(std::any_cast<const Boolean&>(lhs.value).value,
                       std::any_cast<const Boolean&>(rhs.value).value);
        }
        if (lhs.value.type() == typeid(Integer)) {
            return T{}(std::any_cast<const Integer&>(lhs.value).value,
                       std::any_cast<const Integer&>(rhs.value).value);
        }
        if (lhs.value.type() == typeid(Float)) {
            return T{}(std::any_cast<const Float&>(lhs.value).value,
                       std::any_cast<const Float&>(rhs.value).value);
        }
        if (lhs.value.type() == typeid(String)) {
            return T{}(std::any_cast<const String&>(lhs.value).value,
                       std::any_cast<const String&>(rhs.value).value);
        }
        if (lhs.value.type() == typeid(Symbol)) {
            return T{}(std::any_cast<const Symbol&>(lhs.value).value,
                       std::any_cast<const Symbol&>(rhs.value).value);
        }
        if (lhs.value.type() == typeid(Setter)) {
            return T{}(std::any_cast<const Setter&>(lhs.value).value.first,
                       std::any_cast<const Setter&>(rhs.value).value.first);
        }
    }
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Float)) {
        return T{}(std::any_cast<const Integer&>(lhs.value).value,
                   std::any_cast<const Float&>(rhs.value).value);
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Integer)) {
        return T{}(std::any_cast<const Float&>(lhs.value).value,
                   std::any_cast<const Integer&>(rhs.value).value);
    }
    return false;
}

bool operator<(const Object& lhs, const Object& rhs)
{
    return compare<std::less<>>(lhs, rhs);
}

bool operator>(const Object& lhs, const Object& rhs)
{
    return compare<std::greater<>>(lhs, rhs);
}

bool operator<=(const Object& lhs, const Object& rhs)
{
    return compare<std::less_equal<>>(lhs, rhs);
}

bool operator>=(const Object& lhs, const Object& rhs)
{
    return compare<std::greater_equal<>>(lhs, rhs);
}

bool operator==(const Object& lhs, const Object& rhs)
{
    return compare<std::equal_to<>>(lhs, rhs);
}

bool operator!=(const Object& lhs, const Object& rhs)
{
    return !(lhs == rhs);
}

Object operator+(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         + std::any_cast<const Integer&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       + std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Integer&>(lhs.value).value
                       + std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Integer)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       + std::any_cast<const Integer&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(String)
        && rhs.value.type() == typeid(String)) {
        return {String({std::any_cast<const String&>(lhs.value).value
                        + std::any_cast<const String&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator-(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         - std::any_cast<const Integer&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       - std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Integer&>(lhs.value).value
                       - std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Integer)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       - std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator*(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         * std::any_cast<const Integer&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       * std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Integer&>(lhs.value).value
                       * std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Integer)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       * std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator/(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Float(
            {static_cast<double>(std::any_cast<const Integer&>(lhs.value).value)
             / std::any_cast<const Integer&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       / std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Float)) {
        return {Float({std::any_cast<const Integer&>(lhs.value).value
                       / std::any_cast<const Float&>(rhs.value).value})};
    }
    if (lhs.value.type() == typeid(Float)
        && rhs.value.type() == typeid(Integer)) {
        return {Float({std::any_cast<const Float&>(lhs.value).value
                       / std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator%(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         % std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator-(const Object& object)
{
    if (object.value.type() == typeid(Integer)) {
        return {Integer({-std::any_cast<const Integer&>(object.value).value})};
    }
    if (object.value.type() == typeid(Float)) {
        return {Float({-std::any_cast<const Float&>(object.value).value})};
    }
    return object;
}

}  // namespace fundot
