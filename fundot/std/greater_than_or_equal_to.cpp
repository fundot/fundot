#include "greater_than_or_equal_to.h"

namespace fundot {

GreaterThanOrEqualToOperator::GreaterThanOrEqualToOperator(Object* lhs,
                                                           Object* rhs)
    : Pair{lhs, rhs} {
}

std::string GreaterThanOrEqualToOperator::to_string() const {
    return first()->to_string() + " >= " + second()->to_string();
}

Object* GreaterThanOrEqualToOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first()->eval())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '>=' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second()->eval())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '>=' is not a 'Number'"};
    }
    if (typeid(*lhs) == typeid(Integer) && typeid(*rhs) == typeid(Integer)) {
        return new Boolean{lhs->int_value() >= rhs->int_value()};
    }
    return new Boolean{lhs->double_value() >= rhs->double_value()};
}

Object* GreaterThanOrEqualToOperator::quote(std::size_t count) {
    return new GreaterThanOrEqualToOperator{first()->quote(count),
                                            second()->quote(count)};
}

}
