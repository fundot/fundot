#ifndef FUNDOT_STD_ADDITION_H
#define FUNDOT_STD_ADDITION_H

#include "core/parser.h"

namespace fundot {

class AdditionOperator : public Pair {
public:
    AdditionOperator(Object* first, Object* second);

    std::string to_string() const override;

    Object* eval() override;
};

Object* is_addition_operator(Vector* args);

Object* parse_addition_operator(Vector* args);

void register_addition_operator(Parser* parser);

}

#endif
