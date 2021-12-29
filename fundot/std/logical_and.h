#ifndef FUNDOT_STD_LOGICAL_AND_H
#define FUNDOT_STD_LOGICAL_AND_H

#include "fundot/core/parser.h"

namespace fundot {

class LogicalAndOperator : public Pair {
public:
    LogicalAndOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;
};

}

#endif
