#include "fundot/fundot.h"

using namespace fundot;

struct File {
    std::shared_ptr<std::fstream> value;
};

Object close_(const List& list)
{
    if (list.value.size() < 2) {
        return {Null()};
    }
    auto iter = ++list.value.begin();
    if (iter->value.type() == typeid(File)) {
        const File& file = std::any_cast<const File&>(iter->value);
        file.value->close();
        return {Boolean({!file.value->is_open()})};
    }
    return {Null()};
}

Object close_obj = {PrimitiveFunction({close_})};
