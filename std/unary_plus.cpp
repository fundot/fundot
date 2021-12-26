#include "unary_plus.h"

namespace fundot {

UnaryPlusOperator::UnaryPlusOperator(Object* operand) : operand{operand} {
}

std::string UnaryPlusOperator::to_string() const {
    return "+" + operand->to_string();
}

Object* UnaryPlusOperator::eval() {
    auto evaluated{operand->eval()};
    auto int_num{dynamic_cast<Integer*>(evaluated)};
    if (int_num != nullptr) {
        return new Integer{+int_num->int_value()};
    }
    auto double_num{dynamic_cast<Float*>(evaluated)};
    if (double_num != nullptr) {
        return new Float{+double_num->double_value()};
    }
    throw Error{"operand of '+' is neither an 'Integer' nor a 'Float'"};
}

}
