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

Object* NotEqualToOperator::quote(std::size_t count) {
    return new NotEqualToOperator{first()->quote(count),
                                  second()->quote(count)};
}

}
