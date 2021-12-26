#ifndef FUNDOT_STD_DIVISION_H
#define FUNDOT_STD_DIVISION_H

#include "core/parser.h"

namespace fundot {

class DivisionOperator : public Pair {
public:
    DivisionOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
