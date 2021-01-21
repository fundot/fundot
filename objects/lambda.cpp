#include "fundot/fundot.h"

using namespace fundot;

Object lambda_(const List& list)
{
    if (list.value.size() < 3) {
        return {Null()};
    }
    UnorderedSet function;
    auto iter = ++list.value.begin();
    function.value.insert(
        {Setter({{{Symbol({"type"})}, {Symbol({"function"})}}})});
    function.value.insert({Setter({{{Symbol({"params"})}, *iter}})});
    function.value.insert({Setter({{{Symbol({"body"})}, *++iter}})});
    return {function};
}

Object lambda_obj = {SpecialForm({lambda_})};
