#include "unary_minus.h"

namespace fundot {

UnaryMinusOperator::UnaryMinusOperator(Object* operand) : operand{operand} {
}

void UnaryMinusOperator::trace() {
    Object::trace();
    operand->trace();
}

std::string UnaryMinusOperator::to_string() const {
    return "-" + operand->to_string();
}

Object* UnaryMinusOperator::eval() {
    auto evaluated{operand->eval()};
    auto int_num{dynamic_cast<Integer*>(evaluated)};
    if (int_num != nullptr) {
        return new Integer{-int_num->int_value()};
    }
    auto double_num{dynamic_cast<Float*>(evaluated)};
    if (double_num != nullptr) {
        return new Float{-double_num->double_value()};
    }
    throw Error{"operand of '-' is neither an 'Integer' nor a 'Float'"};
}

Object* UnaryMinusOperator::quote(std::size_t count) {
    return new UnaryMinusOperator{operand->quote(count)};
}

}
