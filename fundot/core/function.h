#ifndef FUNDOT_CORE_FUNCTION_H
#define FUNDOT_CORE_FUNCTION_H

#include "vector.h"

namespace fundot {

class PrimitiveFunction : public Object {
public:
    PrimitiveFunction(const std::function<Object*(Vector*)>& raw_function);

    Object* call(Object* obj) override;

    const std::function<Object*(Vector*)>& function_value() const;

private:
    std::function<Object*(Vector*)> raw_function;
};

class SpecialForm : public PrimitiveFunction {
public:
    SpecialForm(const std::function<Object*(Vector*)>& raw_function);

    Object* call(Object* obj) override;
};

}

#endif
