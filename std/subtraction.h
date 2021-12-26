#ifndef FUNDOT_STD_SUBTRACTION_H
#define FUNDOT_STD_SUBTRACTION_H

#include "core/parser.h"

namespace fundot {

class SubtractionOperator : public Pair {
public:
    SubtractionOperator(Object* first, Object* second);

    std::string to_string() const override;

    Object* eval() override;
};

Object* is_subtraction_operator(Vector* args);

Object* parse_subtraction_operator(Vector* args);

void register_subtraction_operator(Parser* parser);

}

#endif
