#ifndef FUNDOT_STD_MULTIPLICATION_H
#define FUNDOT_STD_MULTIPLICATION_H

#include "core/parser.h"

namespace fundot {

class MultiplicationOperator : public Pair {
public:
    MultiplicationOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
