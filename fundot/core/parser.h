#ifndef FUNDOT_CORE_PARSER_H
#define FUNDOT_CORE_PARSER_H

#include "boolean.h"
#include "function.h"
#include "list.h"
#include "null.h"
#include "number.h"
#include "pair.h"
#include "quote.h"
#include "set.h"
#include "string.h"
#include "symbol.h"
#include "vector.h"

namespace fundot {

class Parser : public Object {
public:
    struct Rule {
        Object* predicate;
        Object* expression;
        Integer* precedence;
        String* associativity;
    };

    Parser();

    void trace() override;

    void register_rule(const Rule& rule);

    Object* parse_associated(Vector* args);

    Object* parse_objs(Vector* objs);

    Object* parse(const std::string& str);

    static String* left_to_right;

    static String* right_to_left;

    static Integer* args_parser_pos;

    static Integer* args_precedence_pos;

    static Integer* args_objs_pos;

    static Integer* args_pos_pos;

private:
    using AssociatiedRules = std::pair<std::vector<Rule>, String*>;

    using PrioritizedRules = std::vector<AssociatiedRules>;

    bool is_punctuation(int ch) const;

    Number* next_number(const std::string& str, std::size_t& pos) const;

    String* next_string(const std::string& str, std::size_t& pos) const;

    Symbol* next_symbol(const std::string& str, std::size_t& pos) const;

    Object* next_atom(const std::string& str, std::size_t& pos) const;

    static Object* is_vector(Vector* args);

    static Object* is_set(Vector* args);

    static Object* is_list(Vector* args);

    static Object* is_quote(Vector* args);

    static Object* is_getter(Vector* args);

    static Object* is_setter(Vector* args);

    static Object* parse_vector(Vector* args);

    static Object* parse_set(Vector* args);

    static Object* parse_list(Vector* args);

    static Object* parse_quote(Vector* args);

    static Object* parse_getter(Vector* args);

    static Object* parse_setter(Vector* args);

    static Rule vector_rule;

    static Rule set_rule;

    static Rule list_rule;

    static Rule quote_rule;

    static Rule getter_rule;

    static Rule setter_rule;

    PrioritizedRules rules;
};

}

#endif
