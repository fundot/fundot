#include "logical_and.h"

namespace fundot {

LogicalAndOperator::LogicalAndOperator(Object* lhs, Object* rhs)
    : Pair{lhs, rhs} {
}

std::string LogicalAndOperator::to_string() const {
    return first()->to_string() + " && " + second()->to_string();
}

Object* LogicalAndOperator::eval() {
    Object::Equal equal_to;
    return new Boolean{!equal_to(first()->eval(), new Boolean{false})
                       && !equal_to(second()->eval(), new Boolean{false})};
}

Object* LogicalAndOperator::quote(std::size_t count) {
    return new LogicalAndOperator{first()->quote(count),
                                  second()->quote(count)};
}

}
