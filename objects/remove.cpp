#include "fundot/fundot.h"

using namespace fundot;

Object remove(const UnorderedSet& owner, const Object& value)
{
    UnorderedSet ret = owner;
    auto iter = std::find(ret.value.begin(), ret.value.end(), value);
    if (iter == ret.value.end()) {
        return {Null()};
    }
    ret.value.erase(iter);
    return {ret};
}

Object remove(const Vector& owner, const Object& value)
{
    Vector ret = owner;
    auto iter = std::find(ret.value.begin(), ret.value.end(), value);
    if (iter == ret.value.end()) {
        return {Null()};
    }
    ret.value.erase(iter);
    return {ret};
}

Object remove(const List& owner, const Object& value)
{
    List ret = owner;
    auto iter = std::find(ret.value.begin(), ret.value.end(), value);
    if (iter == ret.value.end()) {
        return {Null()};
    }
    ret.value.erase(iter);
    return {ret};
}

Object remove(const Object& owner, const Object& value)
{
    if (owner.value.type() == typeid(UnorderedSet)) {
        return remove(std::any_cast<const UnorderedSet&>(owner.value), value);
    }
    if (owner.value.type() == typeid(Vector)) {
        return remove(std::any_cast<const Vector&>(owner.value), value);
    }
    if (owner.value.type() == typeid(List)) {
        return remove(std::any_cast<const List&>(owner.value), value);
    }
    return {Null()};
}

Object remove_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return remove(*iter, *++iter);
}

Object remove_obj = {PrimitiveFunction({remove_})};
