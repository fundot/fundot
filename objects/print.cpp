#include <iostream>
#include <sstream>

#include "fundot/fundot.h"

using namespace fundot;

struct File {
    std::shared_ptr<std::fstream> value;
};

Object print_(const List& list)
{
    auto iter = list.value.begin();
    Object to_print;
    Printer print;
    if (++iter == list.value.end()) {
        return {Null()};
    }
    to_print = *iter;
    if (++iter == list.value.end()) {
        print(to_print, std::cout);
        return {Null()};
    }
    std::ostream* os_ptr = &std::cout;
    std::stringstream ss;
    print(to_print, ss);
    iter = std::find(list.value.begin(), list.value.end(),
                     Object({Symbol({"to"})}));
    if (iter != list.value.end()) {
        if (++iter == list.value.end()) {
            throw std::runtime_error("No argument found after 'to'.");
        }
        if (iter->value.type() != typeid(File)) {
            throw std::invalid_argument("Invalid argument after 'to'.");
        }
        os_ptr = std::any_cast<const File&>(iter->value).value.get();
    }
    iter = std::find(list.value.begin(), list.value.end(),
                     Object({Symbol({"for"})}));
    if (iter != list.value.end()) {
        if (++iter == list.value.end()) {
            throw std::runtime_error("No argument found after 'for'.");
        }
        if (*iter != Object({Symbol({"human"})})) {
            throw std::invalid_argument("Invalid argument after 'for'.");
        }
        if (to_print.value.type() == typeid(String)) {
            const std::string& string =
                std::any_cast<const String&>(to_print.value).value;
            ss.str("");
            ss << string;
        }
    }
    *os_ptr << ss.str();
    return {Null()};
}

Object print_obj = {PrimitiveFunction({print_})};
