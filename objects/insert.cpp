#include "fundot/fundot.h"

using namespace fundot;

Object insert(const Vector& owner, const Object& index, const Object& value)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    Vector ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i > ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.emplace(iter, value);
    return {ret};
}

Object insert(const List& owner, const Object& index, const Object& value)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    List ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i > ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.emplace(iter, value);
    return {ret};
}

Object insert(const Object& owner, const Object& index, const Object& value)
{
    if (owner.value.type() == typeid(Vector)) {
        return insert(std::any_cast<const Vector&>(owner.value), index, value);
    }
    if (owner.value.type() == typeid(List)) {
        return insert(std::any_cast<const List&>(owner.value), index, value);
    }
    return {Null()};
}

Object insert_(const List& list)
{
    if (list.value.size() < 4) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return insert(*iter, *++iter, *++iter);
}

Object insert_obj = {PrimitiveFunction({insert_})};
