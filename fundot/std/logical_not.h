#ifndef FUNDOT_STD_LOGICAL_NOT_H
#define FUNDOT_STD_LOGICAL_NOT_H

#include "fundot/core/parser.h"

namespace fundot {

class LogicalNotOperator : public Object {
public:
    LogicalNotOperator(Object* operand);

    void trace() override;

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;

private:
    Object* operand;
};

}

#endif
