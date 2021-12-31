#ifndef FUNDOT_STD_UNARY_PLUS_H
#define FUNDOT_STD_UNARY_PLUS_H

#include "fundot/core/parser.h"

namespace fundot {

class UnaryPlusOperator : public Object {
public:
    UnaryPlusOperator(Object* operand);

    void trace() override;

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;

private:
    Object* operand;
};

}

#endif