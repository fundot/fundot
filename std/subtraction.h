#ifndef FUNDOT_STD_SUBTRACTION_H
#define FUNDOT_STD_SUBTRACTION_H

#include "core/parser.h"

namespace fundot {

class SubtractionOperator : public Pair {
public:
    SubtractionOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
