#ifndef FUNDOT_STD_LOGICAL_OR_H
#define FUNDOT_STD_LOGICAL_OR_H

#include "core/parser.h"

namespace fundot {

class LogicalOrOperator : public Pair {
public:
    LogicalOrOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
