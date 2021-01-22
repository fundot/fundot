#include "fundot/fundot.h"

using namespace fundot;

Object expand_(const List& list)
{
    auto iter = ++list.value.begin();
    if (iter == list.value.end()) {
        return {Null()};
    }
    if (iter->value.type() == typeid(UnorderedSet)) {
        const auto& info = std::any_cast<const UnorderedSet&>(iter->value);
        auto it = info.value.find({Symbol({"type"})});
        if (it == info.value.end()) {
            return *iter;
        }
        if (it->value.type() != typeid(Setter)) {
            return *iter;
        }
        const Object& type =
            std::any_cast<const Setter&>(it->value).value.second;
        if (type != Object({Symbol({"macro"})})) {
            return *iter;
        }
        it = info.value.find({Symbol({"body"})});
        if (it == info.value.end()) {
            return *iter;
        }
        if (it->value.type() != typeid(Setter)) {
            return *iter;
        }
        const Object& body =
            std::any_cast<const Setter&>(it->value).value.second;
        Evaluator eval;
        return eval(*it);
    }
    return *iter;
}

Object expand_obj = {PrimitiveFunction({expand_})};
