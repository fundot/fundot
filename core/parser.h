#ifndef FUNDOT_CORE_PARSER_H
#define FUNDOT_CORE_PARSER_H

#include "boolean.h"
#include "function.h"
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
        Object* condition;
        Object* consequence;
        Integer* precedence;
        String* associativity;
    };

    Parser();

    void trace() override;

    Object* parse_associated(Vector* args);

    Object* parse_objs(Vector* objs);

    Object* parse(const std::string& str);

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

    static Object* is_quote(Vector* args);

    static Object* is_getter(Vector* args);

    static Object* is_setter(Vector* args);

    static Object* parse_vector(Vector* args);

    static Object* parse_set(Vector* args);

    static Object* parse_quote(Vector* args);

    static Object* parse_getter(Vector* args);

    static Object* parse_setter(Vector* args);

    PrioritizedRules rules;
};

}

#endif
