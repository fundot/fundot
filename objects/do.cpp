#include "fundot/fundot.h"

using namespace fundot;

Object do_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    return list.value.back();
}

Object do_obj = {PrimitiveFunction({do_})};
