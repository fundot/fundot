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

Object operator&&(const Object& lhs, const Object& rhs)
{
    bool first = !(lhs.value.type() == typeid(Null)
                   || lhs == Object({Boolean({false})}));
    bool second = !(rhs.value.type() == typeid(Null)
                    || rhs == Object({Boolean({false})}));
    return {Boolean({first && second})};
}

Object operator||(const Object& lhs, const Object& rhs)
{
    bool first = !(lhs.value.type() == typeid(Null)
                   || lhs == Object({Boolean({false})}));
    bool second = !(rhs.value.type() == typeid(Null)
                    || rhs == Object({Boolean({false})}));
    return {Boolean({first || second})};
}

Object operator!(const Object& object)
{
    return {Boolean({object.value.type() == typeid(Null)
                     || object == Object({Boolean({false})})})};
}

Object operator&(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         & std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator|(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         | std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator^(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         ^ std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator~(const Object& object)
{
    if (object.value.type() == typeid(Integer)) {
        return {Integer({~std::any_cast<const Integer&>(object.value).value})};
    }
    return {Null()};
}

Object operator<<(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         << std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object operator>>(const Object& lhs, const Object& rhs)
{
    if (lhs.value.type() == typeid(Integer)
        && rhs.value.type() == typeid(Integer)) {
        return {Integer({std::any_cast<const Integer&>(lhs.value).value
                         >> std::any_cast<const Integer&>(rhs.value).value})};
    }
    return {Null()};
}

Object* get(Vector& owner, const Integer& integer)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        return &owner.value[integer.value];
    }
    return nullptr;
}

Object* get(Vector& owner, const Object& index)
{
    if (index.value.type() == typeid(Integer)) {
        return get(owner, std::any_cast<const Integer&>(index.value));
    }
    return nullptr;
}

Object* get(UnorderedSet& owner, const Object& index)
{
    auto iter = owner.value.find(index);
    if (iter != owner.value.end()) {
        if (iter->value.type() == typeid(Setter)) {
            return &const_cast<Object&>(
                std::any_cast<const Setter&>(iter->value).value.second);
        }
        return &const_cast<Object&>(*iter);
    }
    return nullptr;
}

Object* get(Object& owner, const Getter& getter)
{
    Object* obj_ptr = get(owner, getter.value.first);
    if (obj_ptr != nullptr) {
        return get(*obj_ptr, getter.value.second);
    }
    return nullptr;
}

Object* get(Object& owner, const Object& index)
{
    if (index.value.type() == typeid(Getter)) {
        return get(owner, std::any_cast<const Getter&>(index.value));
    }
    if (owner.value.type() == typeid(UnorderedSet)) {
        return get(std::any_cast<UnorderedSet&>(owner.value), index);
    }
    if (owner.value.type() == typeid(Vector)) {
        return get(std::any_cast<Vector&>(owner.value), index);
    }
    return nullptr;
}

void set(Vector& owner, const Integer& integer, const Object& value)
{
    if (static_cast<std::size_t>(integer.value) < owner.value.size()) {
        owner.value[integer.value] = value;
    }
}

void set(Vector& owner, const Object& index, const Object& value)
{
    if (index.value.type() == typeid(Integer)) {
        set(owner, std::any_cast<const Integer&>(index.value), value);
    }
}

void set(UnorderedSet& owner, const Object& index, const Object& value)
{
    owner.value.erase({Setter({{index, value}})});
    owner.value.insert({Setter({{index, value}})});
}

void set(Object& owner, const Getter& index, const Object& value)
{
    set(*get(owner, index.value.first), index.value.second, value);
}

void set(Object& owner, const Object& index, const Object& value)
{
    if (index.value.type() == typeid(Getter)) {
        set(owner, std::any_cast<const Getter&>(index.value), value);
    }
    if (owner.value.type() == typeid(UnorderedSet)) {
        set(std::any_cast<UnorderedSet&>(owner.value), index, value);
    }
    if (owner.value.type() == typeid(Vector)) {
        set(std::any_cast<Vector&>(owner.value), index, value);
    }
}

}  // namespace fundot
