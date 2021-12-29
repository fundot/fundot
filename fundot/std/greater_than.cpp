#include "greater_than.h"

namespace fundot {

GreaterThanOperator::GreaterThanOperator(Object* lhs, Object* rhs)
    : Pair{lhs, rhs} {
}

std::string GreaterThanOperator::to_string() const {
    return first()->to_string() + " > " + second()->to_string();
}

Object* GreaterThanOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first()->eval())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '>' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second()->eval())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '>' is not a 'Number'"};
    }
    if (typeid(*lhs) == typeid(Integer) && typeid(*rhs) == typeid(Integer)) {
        return new Boolean{lhs->int_value() > rhs->int_value()};
    }
    return new Boolean{lhs->double_value() > rhs->double_value()};
}

Object* GreaterThanOperator::quote(std::size_t count) {
    return new GreaterThanOperator{first()->quote(count),
                                   second()->quote(count)};
}

}
