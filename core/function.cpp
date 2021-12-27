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
    for (std::size_t i{0}, size{args->size()}; i < size; ++i) {
        args->set(new Integer{static_cast<int>(i)}, args->at(i)->eval());
    }
    return raw_function(args);
}

const std::function<Object*(Vector*)>& PrimitiveFunction::function_value()
    const {
    return raw_function;
}

SpecialForm::SpecialForm(const std::function<Object*(Vector*)>& raw_function)
    : PrimitiveFunction(raw_function) {
}

Object* SpecialForm::call(Object* obj) {
    auto args{dynamic_cast<Vector*>(obj)};
    if (args == nullptr) {
        throw Error{"argument is not a 'Vector'"};
    }
    return function_value()(args);
}

}
