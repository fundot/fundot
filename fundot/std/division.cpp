#include "division.h"

namespace fundot {

DivisionOperator::DivisionOperator(Object* lhs, Object* rhs) : Pair{lhs, rhs} {
}

std::string DivisionOperator::to_string() const {
    return first()->to_string() + " / " + second()->to_string();
}

Object* DivisionOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first()->eval())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '/' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second()->eval())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '/' is not a 'Number'"};
    }
    return new Float{lhs->double_value() / rhs->double_value()};
}

}
