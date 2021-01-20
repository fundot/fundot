#include "fundot/fundot.h"

using namespace fundot;

Object append(const Vector& owner, const Object& value)
{
    Vector ret = owner;
    ret.value.emplace_back(value);
    return {ret};
}

Object append(const List& owner, const Object& value)
{
    List ret = owner;
    ret.value.emplace_back(value);
    return {ret};
}

Object append(const Object& owner, const Object& value)
{
    if (owner.value.type() == typeid(Vector)) {
        return append(std::any_cast<const Vector&>(owner.value), value);
    }
    if (owner.value.type() == typeid(List)) {
        return append(std::any_cast<const List&>(owner.value), value);
    }
    return {Null()};
}

Object append_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return append(*iter, *++iter);
}

Object append_obj = {PrimitiveFunction({append_})};
