#ifndef FUNDOT_STD_LOGICAL_NOT_H
#define FUNDOT_STD_LOGICAL_NOT_H

#include "fundot/core/parser.h"

namespace fundot {

class LogicalNotOperator : public Object {
public:
    LogicalNotOperator(Object* operand);

    void traverse(const Visitor& visit) override;

    void trace() override;

    std::string to_string() const override;

    Object* eval() override;

private:
    Object* operand;
};

}

#endif
