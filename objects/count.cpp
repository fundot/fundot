#include "fundot/fundot.h"

using namespace fundot;

Object count_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    Integer size = {0};
    if (iter->value.type() == typeid(String)) {
        size.value = std::any_cast<const String&>(iter->value).value.size();
        return {size};
    }
    if (iter->value.type() == typeid(UnorderedSet)) {
        size.value =
            std::any_cast<const UnorderedSet&>(iter->value).value.size();
        return {size};
    }
    if (iter->value.type() == typeid(Vector)) {
        size.value = std::any_cast<const Vector&>(iter->value).value.size();
        return {size};
    }
    if (iter->value.type() == typeid(List)) {
        size.value = std::any_cast<const List&>(iter->value).value.size();
        return {size};
    }
    return list.value.back();
}

Object count_obj = {PrimitiveFunction({count_})};
