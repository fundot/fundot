#ifndef FUNDOT_STD_MODULO_H
#define FUNDOT_STD_MODULO_H

#include "fundot/core/parser.h"

namespace fundot {

class ModuloOperator : public Pair {
public:
    ModuloOperator(Object* lhs, Object* rhs);

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;
};

}

#endif