#include "builtins.h"

namespace fundot {

static Object* is_unary_plus_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"+"})
                       && (pos->int_value() == 0)};
}

static Object* is_unary_minus_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"-"})
                       && (pos->int_value() == 0)};
}

static Object* is_addition_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"+"})};
}

static Object* is_subtraction_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"-"})};
}

static Object* is_multiplication_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"*"})};
}

static Object* is_division_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"/"})};
}

static Object* is_modulo_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"%"})};
}

static Object* is_equal_to_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{"="})
        && pos->int_value() < objs->size() - 1
        && objs->at(pos->int_value() + 1)->equals(new Symbol{"="})};
}

static Object* is_not_equal_to_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{"!"})
        && pos->int_value() < objs->size() - 1
        && objs->at(pos->int_value() + 1)->equals(new Symbol{"="})};
}

static Object* is_less_than_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{"<"})};
}

static Object* is_greater_than_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{objs->get(pos)->equals(new Symbol{">"})};
}

static Object* is_less_than_or_equal_to_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{"<"})
        && pos->int_value() < objs->size() - 1
        && objs->at(pos->int_value() + 1)->equals(new Symbol{"="})};
}

static Object* is_greater_than_or_equal_to_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{">"})
        && pos->int_value() < objs->size() - 1
        && objs->at(pos->int_value() + 1)->equals(new Symbol{"="})};
}

static Object* is_logical_not_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{"!"})
        && pos->int_value() < objs->size() - 1
        && !objs->at(pos->int_value() + 1)->equals(new Symbol{"="})};
}

static Object* is_logical_and_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{"&"})
        && pos->int_value() < objs->size() - 1
        && objs->at(pos->int_value() + 1)->equals(new Symbol{"&"})};
}

static Object* is_logical_or_operator(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    return new Boolean{
        objs->get(pos)->equals(new Symbol{"|"})
        && pos->int_value() < objs->size() - 1
        && objs->at(pos->int_value() + 1)->equals(new Symbol{"|"})};
}

static Object* parse_unary_plus_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto operand_pos{pos->int_value() + 1};
    auto unary_plus_operator{(new UnaryPlusOperator{objs->at(operand_pos)})};
    auto evaluated{unary_plus_operator->eval()};
    objs->erase(operand_pos);
    objs->set(pos, evaluated);
    return evaluated;
}

static Object* parse_unary_minus_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto operand_pos{pos->int_value() + 1};
    auto unary_minus_operator{(new UnaryMinusOperator{objs->at(operand_pos)})};
    auto evaluated{unary_minus_operator->eval()};
    objs->erase(operand_pos);
    objs->set(pos, evaluated);
    return evaluated;
}

static Object* parse_addition_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto addition_operator{
        new AdditionOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, addition_operator);
    return addition_operator;
}

static Object* parse_subtraction_operator(Vector* args) {
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

static Object* parse_multiplication_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto multiplication_operator{
        new MultiplicationOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, multiplication_operator);
    return multiplication_operator;
}

static Object* parse_division_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto division_operator{
        new DivisionOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, division_operator);
    return division_operator;
}

static Object* parse_modulo_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto modulo_operator{
        new ModuloOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, modulo_operator);
    return modulo_operator;
}

static Object* parse_equal_to_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 2};
    auto equal_to_operator{
        new EqualToOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(rhs_pos - 1);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, equal_to_operator);
    return equal_to_operator;
}

static Object* parse_not_equal_to_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 2};
    auto not_equal_to_operator{
        new NotEqualToOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(rhs_pos - 1);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, not_equal_to_operator);
    return not_equal_to_operator;
}

static Object* parse_less_than_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto less_than_operator{
        new LessThanOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, less_than_operator);
    return less_than_operator;
}

static Object* parse_greater_than_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 1};
    auto greater_than_operator{
        new GreaterThanOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, greater_than_operator);
    return greater_than_operator;
}

static Object* parse_less_than_or_equal_to_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 2};
    auto less_than_or_equal_to_operator{
        new LessThanOrEqualToOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(rhs_pos - 1);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, less_than_or_equal_to_operator);
    return less_than_or_equal_to_operator;
}

static Object* parse_greater_than_or_equal_to_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 2};
    auto greater_than_or_equal_to_operator{
        new GreaterThanOrEqualToOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(rhs_pos - 1);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, greater_than_or_equal_to_operator);
    return greater_than_or_equal_to_operator;
}

static Object* parse_logical_not_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto operand_pos{pos->int_value() + 1};
    auto logical_not{new LogicalNotOperator{objs->at(operand_pos)}};
    objs->erase(operand_pos);
    objs->set(pos, logical_not);
    return logical_not;
}

static Object* parse_logical_and_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 2};
    auto logical_and_operator{
        new LogicalAndOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(rhs_pos - 1);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, logical_and_operator);
    return logical_and_operator;
}

static Object* parse_logical_or_operator(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(Parser::args_parser_pos))};
    auto precedence{
        dynamic_cast<Integer*>(args->get(Parser::args_precedence_pos))};
    auto objs{dynamic_cast<Vector*>(args->get(Parser::args_objs_pos))};
    auto pos{dynamic_cast<Integer*>(args->get(Parser::args_pos_pos))};
    auto lhs_pos{pos->int_value() - 1};
    auto rhs_pos{pos->int_value() + 2};
    auto logical_or_operator{
        new LogicalOrOperator{objs->at(lhs_pos), objs->at(rhs_pos)}
    };
    objs->erase(rhs_pos);
    objs->erase(rhs_pos - 1);
    objs->erase(pos->int_value());
    pos = new Integer{lhs_pos};
    args->set(Parser::args_pos_pos, pos);
    objs->set(pos, logical_or_operator);
    return logical_or_operator;
}

static void register_unary_plus_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_unary_plus_operator},
                           new SpecialForm{parse_unary_plus_operator},
                           new Integer{4},
                           Parser::right_to_left});
}

static void register_unary_minus_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_unary_minus_operator},
                           new SpecialForm{parse_unary_minus_operator},
                           new Integer{4},
                           Parser::right_to_left});
}

static void register_addition_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_addition_operator},
                           new SpecialForm{parse_addition_operator},
                           new Integer{6},
                           Parser::left_to_right});
}

static void register_subtraction_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_subtraction_operator},
                           new SpecialForm{parse_subtraction_operator},
                           new Integer{6},
                           Parser::left_to_right});
}

static void register_multiplication_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_multiplication_operator},
                           new SpecialForm{parse_multiplication_operator},
                           new Integer{5},
                           Parser::left_to_right});
}

static void register_division_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_division_operator},
                           new SpecialForm{parse_division_operator},
                           new Integer{5},
                           Parser::left_to_right});
}

static void register_modulo_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_modulo_operator},
                           new SpecialForm{parse_modulo_operator},
                           new Integer{5},
                           Parser::left_to_right});
}

static void register_equal_to_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_equal_to_operator},
                           new SpecialForm{parse_equal_to_operator},
                           new Integer{9},
                           Parser::left_to_right});
}

static void register_not_equal_to_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_not_equal_to_operator},
                           new SpecialForm{parse_not_equal_to_operator},
                           new Integer{9},
                           Parser::left_to_right});
}

static void register_less_than_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_less_than_operator},
                           new SpecialForm{parse_less_than_operator},
                           new Integer{8},
                           Parser::left_to_right});
}

static void register_greater_than_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_greater_than_operator},
                           new SpecialForm{parse_greater_than_operator},
                           new Integer{8},
                           Parser::left_to_right});
}

static void register_less_than_or_equal_to_operator(Parser* parser) {
    parser->register_rule(
        {new SpecialForm{is_less_than_or_equal_to_operator},
         new SpecialForm{parse_less_than_or_equal_to_operator},
         new Integer{7},
         Parser::left_to_right});
}

static void register_greater_than_or_equal_to_operator(Parser* parser) {
    parser->register_rule(
        {new SpecialForm{is_greater_than_or_equal_to_operator},
         new SpecialForm{parse_greater_than_or_equal_to_operator},
         new Integer{7},
         Parser::left_to_right});
}

static void register_logical_not_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_logical_not_operator},
                           new SpecialForm{parse_logical_not_operator},
                           new Integer{4},
                           Parser::right_to_left});
}

static void register_logical_and_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_logical_and_operator},
                           new SpecialForm{parse_logical_and_operator},
                           new Integer{9},
                           Parser::left_to_right});
}

static void register_logical_or_operator(Parser* parser) {
    parser->register_rule({new SpecialForm{is_logical_or_operator},
                           new SpecialForm{parse_logical_or_operator},
                           new Integer{10},
                           Parser::left_to_right});
}

void load_builtins(Object* obj) {
    auto parser{dynamic_cast<Parser*>(
        Object::get_scope()->get(new Symbol{"__parser__"}))};
    register_unary_plus_operator(parser);
    register_unary_minus_operator(parser);
    register_addition_operator(parser);
    register_subtraction_operator(parser);
    register_multiplication_operator(parser);
    register_division_operator(parser);
    register_modulo_operator(parser);
    register_equal_to_operator(parser);
    register_not_equal_to_operator(parser);
    register_less_than_operator(parser);
    register_greater_than_operator(parser);
    register_less_than_or_equal_to_operator(parser);
    register_greater_than_or_equal_to_operator(parser);
    register_logical_not_operator(parser);
    register_logical_and_operator(parser);
    register_logical_or_operator(parser);
    obj->set(new Symbol{"cond"}, new SpecialForm{builtin_cond});
    obj->set(new Symbol{"while"}, new SpecialForm{builtin_while});
    obj->set(new Symbol{"conj"}, new PrimitiveFunction{builtin_conj});
    obj->set(new Symbol{"count"}, new PrimitiveFunction{builtin_count});
    obj->set(new Symbol{"print"}, new PrimitiveFunction{builtin_print});
}

}
