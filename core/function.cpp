#include "function.h"
#include <cstdarg>

namespace fundot {

PrimitiveFunction::PrimitiveFunction(
    const std::function<Object*(Vector*)>& raw_function)
    : raw_function(raw_function) {
}

Object* PrimitiveFunction::call(Object* obj) {
    auto args{dynamic_cast<Vector*>(obj)};
    if (args == nullptr) {
        throw Error{"argument is not a 'Vector'"};
    }
    return raw_function(args);
}

SpecialForm::SpecialForm(const std::function<Object*(Vector*)>& raw_function)
    : PrimitiveFunction(raw_function) {
}

}
