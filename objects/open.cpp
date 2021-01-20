#include "fundot/fundot.h"

using namespace fundot;

Object open_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() != typeid(String)) {
        return {Null()};
    }
    const String& file_name = std::any_cast<const String&>(iter->value);
    std::ios::openmode mode = std::ios::in;
    if (++iter != list.value.end()) {
        if (*iter == Object({String({"w"})})) {
            mode = std::ios::out;
        }
        if (*iter == Object({String({"a"})})) {
            mode = std::ios::app;
        }
        if (*iter == Object({String({"b"})})) {
            mode = std::ios::binary;
        }
        if (*iter == Object({String({"+"})})) {
            mode = std::ios::in | std::ios::out;
        }
    }
    File file({std::make_shared<std::fstream>(file_name.value, mode)});
    if (file.value->is_open()) {
        return {file};
    }
    return {Null()};
}

Object open_obj = {PrimitiveFunction({open_})};
