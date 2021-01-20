#include <iostream>

#include "fundot/fundot.h"

using namespace fundot;

Object read_(const List& list)
{
    Object object = {Null()};
    Reader read;
    if (list.value.size() == 1) {
        read(object, std::cin);
        return object;
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() == typeid(File)) {
        read(object, *std::any_cast<const File&>(iter->value).value);
    }
    return object;
}

Object read_obj = {PrimitiveFunction({read_})};
