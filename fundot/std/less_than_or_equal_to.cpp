#include "less_than_or_equal_to.h"

namespace fundot {

LessThanOrEqualToOperator::LessThanOrEqualToOperator(Object* lhs, Object* rhs)
    : Pair{lhs, rhs} {
}

std::string LessThanOrEqualToOperator::to_string() const {
    return first()->to_string() + " <= " + second()->to_string();
}

Object* LessThanOrEqualToOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first()->eval())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '<=' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second()->eval())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '<=' is not a 'Number'"};
    }
    if (typeid(*lhs) == typeid(Integer) && typeid(*rhs) == typeid(Integer)) {
        return new Boolean{lhs->int_value() <= rhs->int_value()};
    }
    return new Boolean{lhs->double_value() <= rhs->double_value()};
}

Object* LessThanOrEqualToOperator::quote(std::size_t count) {
    return new LessThanOrEqualToOperator{first()->quote(count),
                                         second()->quote(count)};
}

}
