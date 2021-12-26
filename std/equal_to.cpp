#include "equal_to.h"

namespace fundot {

EqualToOperator::EqualToOperator(Object* lhs, Object* rhs) : Pair{lhs, rhs} {
}

std::string EqualToOperator::to_string() const {
    return first()->to_string() + " == " + second()->to_string();
}

Object* EqualToOperator::eval() {
    return new Boolean{Object::Equal{}(first()->eval(), second()->eval())};
}

}
