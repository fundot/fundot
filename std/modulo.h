#ifndef FUNDOT_STD_MODULO_H
#define FUNDOT_STD_MODULO_H

#include "core/parser.h"

namespace fundot {

class ModuloOperator : public Pair {
public:
    ModuloOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
