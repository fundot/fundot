#ifndef FUNDOT_STD_LESS_THAN_H
#define FUNDOT_STD_LESS_THAN_H

#include "fundot/core/parser.h"

namespace fundot {

class LessThanOperator : public Pair {
public:
    LessThanOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;
};

}

#endif
