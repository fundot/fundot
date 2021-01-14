#ifndef FUNDOT_EVAL_H
#define FUNDOT_EVAL_H

#include <unordered_map>

#include "fundot_io.h"

namespace fundot {

class Evaluator {
public:
    Object operator()(const Object& object);

private:
    UnorderedSet scope_;

    Object global(const List&);

    Object eval(const Adder& adder);

    Object eval(const Subtractor& subtractor);

    Object eval(const Multiplier& multiplier);

    Object eval(const Divisor& divisor);

    Object eval(const Modular& modular);

    Object eval(const Negator& negator);

    Object eval(const Less& less);

    Object eval(const Greater& greater);

    Object eval(const LessEqual& less_equal);

    Object eval(const GreaterEqual& greater_equal);

    Object eval(const EqualTo& equal_to);

    Object eval(const NotEqualTo& not_equal_to);

    Object eval(const And& logical_and);

    Object eval(const Or& logical_or);

    Object eval(const Not& logical_not);

    Object eval(const BitwiseAnd& bitwise_and);

    Object eval(const BitwiseOr& bitwise_or);

    Object eval(const BitwiseXor& bitwise_xor);

    Object eval(const BitwiseNot& bitwise_not);

    Object eval(const LeftShift& left_shift);

    Object eval(const RightShift& right_shift);

    Object eval(const Symbol& symbol);

    Object eval(const Getter& getter);

    Object eval(const Setter& setter);

    Object eval(const List& list);

    Object eval(const Quote& quote);

    Object eval(const Object& object);
};

}  // namespace fundot

#endif
