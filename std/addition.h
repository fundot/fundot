#ifndef FUNDOT_STD_ADDITION_H
#define FUNDOT_STD_ADDITION_H

#include "core/parser.h"

namespace fundot {

class AdditionOperator : public Pair {
public:
    AdditionOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
