#ifndef FUNDOT_STD_LESS_THAN_OR_EQUAL_TO_H
#define FUNDOT_STD_LESS_THAN_OR_EQUAL_TO_H

#include "fundot/core/parser.h"

namespace fundot {

class LessThanOrEqualToOperator : public Pair {
public:
    LessThanOrEqualToOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;
};

}

#endif
