#include "subtraction.h"

namespace fundot {

SubtractionOperator::SubtractionOperator(Object* lhs, Object* rhs)
    : Pair{lhs, rhs} {
}

std::string SubtractionOperator::to_string() const {
    return first()->to_string() + " - " + second()->to_string();
}

Object* SubtractionOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first()->eval())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '-' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second()->eval())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '-' is not a 'Number'"};
    }
    if (typeid(*lhs) == typeid(Integer) && typeid(*rhs) == typeid(Integer)) {
        return new Integer{lhs->int_value() - rhs->int_value()};
    }
    return new Float{lhs->double_value() - rhs->double_value()};
}

}
