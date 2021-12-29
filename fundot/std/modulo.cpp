#include "modulo.h"
#include <cmath>

namespace fundot {

ModuloOperator::ModuloOperator(Object* lhs, Object* rhs) : Pair{lhs, rhs} {
}

std::string ModuloOperator::to_string() const {
    return first()->to_string() + " % " + second()->to_string();
}

Object* ModuloOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first()->eval())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '%' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second()->eval())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '%' is not a 'Number'"};
    }
    return new Float{std::fmod(lhs->double_value(), rhs->double_value())};
}

Object* ModuloOperator::quote(std::size_t count) {
    return new ModuloOperator{first()->quote(count), second()->quote(count)};
}

}
