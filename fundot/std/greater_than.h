#ifndef FUNDOT_STD_GREATER_THAN_H
#define FUNDOT_STD_GREATER_THAN_H

#include "fundot/core/parser.h"

namespace fundot {

class GreaterThanOperator : public Pair {
public:
    GreaterThanOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;
};

}

#endif
