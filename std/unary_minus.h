#ifndef FUNDOT_STD_UNARY_MINUS_H
#define FUNDOT_STD_UNARY_MINUS_H

#include "core/parser.h"

namespace fundot {

class UnaryMinusOperator : public Object {
public:
    UnaryMinusOperator(Object* operand);

    void trace() override;

    std::string to_string() const override;

    Object* eval() override;

private:
    Object* operand;
};

}

#endif
