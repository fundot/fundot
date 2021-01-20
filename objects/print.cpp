#include <iostream>

#include "fundot/fundot.h"

using namespace fundot;

Object print_(const List& list)
{
    std::string end = "\n";
    auto iter = list.value.begin();
    Object to_print;
    Printer print;
    if (++iter == list.value.end()) {
        std::cout << end;
        return {Void()};
    }
    to_print = *iter;
    if (++iter == list.value.end()) {
        print(to_print, std::cout);
        std::cout << end;
        return {Void()};
    }
    if (iter->value.type() == typeid(File)) {
        print(to_print, *std::any_cast<const File&>(iter->value).value);
        *std::any_cast<const File&>(iter->value).value << end;
        return {Void()};
    }
    return {Void()};
}

Object print_obj = {PrimitiveFunction({print_})};
