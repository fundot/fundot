#include "logical_not.h"

namespace fundot {

LogicalNotOperator::LogicalNotOperator(Object* operand) : operand(operand) {
}

void LogicalNotOperator::traverse(const Visitor& visit) {
    visit(operand);
}

void LogicalNotOperator::trace() {
    Object::trace();
    operand->trace();
}

std::string LogicalNotOperator::to_string() const {
    return "!" + operand->to_string();
}

Object* LogicalNotOperator::eval() {
    return new Boolean{Object::Equal{}(operand->eval(), new Boolean{false})};
}

}
