#include "fundot/fundot.h"

using namespace fundot;

Object lambda_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    return {Function({*iter, *++iter})};
}

Object lambda_obj = {SpecialForm({lambda_})};
