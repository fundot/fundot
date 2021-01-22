#include "fundot/fundot.h"

using namespace fundot;

Object quote_(const List& list)
{
    auto iter = ++list.value.begin();
    if (iter != list.value.end()) {
        return *iter;
    }
    return {Null()};
}

Object quote_obj = {SpecialForm({quote_})};
