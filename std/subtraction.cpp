#include "subtraction.h"

namespace fundot {

SubtractionOperator::SubtractionOperator(Object* first, Object* second)
    : Pair{first, second} {
}

std::string SubtractionOperator::to_string() const {
    return first()->to_string() + " - " + second()->to_string();
}

Object* SubtractionOperator::eval() {
    auto lhs{dynamic_cast<Number*>(first())};
    if (lhs == nullptr) {
        throw Object::Error{"left hand side of '-' is not a 'Number'"};
    }
    auto rhs{dynamic_cast<Number*>(second())};
    if (rhs == nullptr) {
        throw Object::Error{"right hand side of '-' is not a 'Number'"};
    }
    if (typeid(*lhs) == typeid(Integer) && typeid(*rhs) == typeid(Integer)) {
        return new Integer{lhs->int_value() - rhs->int_value()};
    }
    return new Float{lhs->double_value() - rhs->double_value()};
}

Object* is_subtraction_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    if (objs->get(pos)->equals(new Symbol{"-"})) {
        return new Boolean{true};
    }
    return new Boolean{false};
}

Object* parse_subtraction_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto subtraction_operator{
        new SubtractionOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, subtraction_operator);
    return subtraction_operator;
}

void register_subtraction_operator(Parser* parser) {
    parser->register_rule({new PrimitiveFunction{is_subtraction_operator},
                           new PrimitiveFunction{parse_subtraction_operator},
                           new Integer{4},
                           Parser::left_to_right});
}

}
