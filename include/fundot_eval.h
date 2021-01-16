#ifndef FUNDOT_EVAL_H
#define FUNDOT_EVAL_H

#include <unordered_map>

#include "fundot_io.h"

namespace fundot {

class Evaluator {
public:
    Object operator()(const Object& object);

private:
    Object scope_ = {UnorderedSet()};

    Object* get(Vector& owner, const Integer& integer);

    Object* get(Vector& owner, const Object& index);

    Object* get(UnorderedSet& owner, const Object& index);

    Object* get(Function& owner, const Object& index);

    Object* get(List& owner, const Integer& integer);

    Object* get(List& owner, const Object& index);

    Object* get(Object& owner, const Getter& getter);

    Object* get(Object& owner, const Object& index);

    void set(Vector& owner, const Integer& integer, const Object& value);

    void set(Vector& owner, const Object& index, const Object& value);

    void set(UnorderedSet& owner, const Object& index, const Object& value);

    void set(Function& owner, const Object& index, const Object& value);

    void set(List& owner, const Integer& index, const Object& value);

    void set(List& owner, const Object& index, const Object& value);

    void set(Object& owner, const Getter& index, const Object& value);

    void set(Object& owner, const Object& index, const Object& value);

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

    Object eval(const Assignment& assignment);

    Object eval(const List& list);

    Object eval(const UnorderedSet& set);

    Object eval(const Quote& quote);

    Object eval(const Object& object);
};

}  // namespace fundot

#endif
