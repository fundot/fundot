#include "logical_or.h"

namespace fundot {

LogicalOrOperator::LogicalOrOperator(Object* lhs, Object* rhs)
    : Pair{lhs, rhs} {
}

std::string LogicalOrOperator::to_string() const {
    return first()->to_string() + " || " + second()->to_string();
}

Object* LogicalOrOperator::eval() {
    Object::Equal equal_to;
    return new Boolean{!equal_to(first()->eval(), new Boolean{false})
                       || !equal_to(second()->eval(), new Boolean{false})};
}

}
