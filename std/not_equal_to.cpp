#include "not_equal_to.h"

namespace fundot {

NotEqualToOperator::NotEqualToOperator(Object* lhs, Object* rhs)
    : Pair{lhs, rhs} {
}

std::string NotEqualToOperator::to_string() const {
    return first()->to_string() + " != " + second()->to_string();
}

Object* NotEqualToOperator::eval() {
    return new Boolean{!Object::Equal{}(first()->eval(), second()->eval())};
}

}
