#ifndef FUNDOT_STD_GREATER_THAN_OR_EQUAL_TO_H
#define FUNDOT_STD_GREATER_THAN_OR_EQUAL_TO_H

#include "fundot/core/parser.h"

namespace fundot {

class GreaterThanOrEqualToOperator : public Pair {
public:
    GreaterThanOrEqualToOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
