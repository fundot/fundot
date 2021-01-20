#include "fundot/fundot.h"

using namespace fundot;

Object pop(const Vector& owner, const Object& index)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    Vector ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i >= ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.erase(iter);
    return {ret};
}

Object pop(const List& owner, const Object& index)
{
    if (index.value.type() != typeid(Integer)) {
        return {Null()};
    }
    List ret = owner;
    std::size_t i = std::any_cast<const Integer&>(index.value).value;
    if (i >= ret.value.size()) {
        return {Null()};
    }
    auto iter = ret.value.begin();
    std::advance(iter, i);
    ret.value.erase(iter);
    return {ret};
}

Object pop(const Object& owner, const Object& index)
{
    if (owner.value.type() == typeid(Vector)) {
        return pop(std::any_cast<const Vector&>(owner.value), index);
    }
    if (owner.value.type() == typeid(List)) {
        return pop(std::any_cast<const List&>(owner.value), index);
    }
    return {Null()};
}

Object pop(const Vector& owner)
{
    if (owner.value.empty()) {
        return {Null()};
    }
    Vector ret = owner;
    ret.value.pop_back();
    return {ret};
}

Object pop(const List& owner)
{
    if (owner.value.empty()) {
        return {Null()};
    }
    List ret = owner;
    ret.value.pop_back();
    return {ret};
}

Object pop(const Object& owner)
{
    if (owner.value.type() == typeid(Vector)) {
        return pop(std::any_cast<const Vector&>(owner.value));
    }
    if (owner.value.type() == typeid(List)) {
        return pop(std::any_cast<const List&>(owner.value));
    }
    return {Null()};
}

Object pop_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    if (list.value.size() == 2) {
        return pop(*iter);
    }
    return pop(*iter, *++iter);
}

Object pop_obj = {PrimitiveFunction({pop_})};
