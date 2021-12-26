#ifndef FUNDOT_STD_NOT_EQUAL_TO_H
#define FUNDOT_STD_NOT_EQUAL_TO_H

#include "core/parser.h"

namespace fundot {

class NotEqualToOperator : public Pair {
public:
    NotEqualToOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
