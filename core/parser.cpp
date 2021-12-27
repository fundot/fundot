#include "parser.h"
#include <sstream>

namespace fundot {

String* Parser::left_to_right{new String{"left_to_right"}};

String* Parser::right_to_left{new String{"right_to_left"}};

Integer* Parser::args_parser_pos{new Integer{0}};

Integer* Parser::args_precedence_pos{new Integer{1}};

Integer* Parser::args_objs_pos{new Integer{2}};

Integer* Parser::args_pos_pos{new Integer{3}};

Parser::Rule Parser::vector_rule{new SpecialForm{Parser::is_vector},
                                 new SpecialForm{Parser::parse_vector},
                                 new Integer{0},
                                 left_to_right};

Parser::Rule Parser::set_rule{new SpecialForm{Parser::is_set},
                              new SpecialForm{Parser::parse_set},
                              new Integer{0},
                              left_to_right};

Parser::Rule Parser::list_rule{new SpecialForm{Parser::is_list},
                               new SpecialForm{Parser::parse_list},
                               new Integer{0},
                               left_to_right};

Parser::Rule Parser::quote_rule{new SpecialForm{Parser::is_quote},
                                new SpecialForm{Parser::parse_quote},
                                new Integer{1},
                                left_to_right};

Parser::Rule Parser::getter_rule{new SpecialForm{Parser::is_getter},
                                 new SpecialForm{Parser::parse_getter},
                                 new Integer{2},
                                 left_to_right};

Parser::Rule Parser::setter_rule{new SpecialForm{Parser::is_setter},
                                 new SpecialForm{Parser::parse_setter},
                                 new Integer{32},
                                 right_to_left};

Parser::Parser() {
    register_rule(vector_rule);
    register_rule(set_rule);
    register_rule(list_rule);
    register_rule(quote_rule);
    register_rule(getter_rule);
    register_rule(setter_rule);
}

void Parser::trace() {
    Object::trace();
    left_to_right->mark();
    right_to_left->mark();
    args_parser_pos->mark();
    args_precedence_pos->mark();
    args_objs_pos->mark();
    args_pos_pos->mark();
    for (auto& associated : rules) {
        if (associated.second == nullptr) {
            continue;
        }
        associated.second->mark();
        for (auto& rule : associated.first) {
            rule.predicate->mark();
            rule.expression->mark();
            rule.precedence->mark();
            rule.associativity->mark();
        }
    }
}

void Parser::register_rule(const Rule& rule) {
    auto rule_pos{static_cast<std::size_t>(rule.precedence->int_value())};
    if (rule_pos >= rules.size()) {
        rules.resize(rule_pos + 1);
        rules[rule_pos] = {{rule}, rule.associativity};
        return;
    }
    if (rules[rule_pos].second == nullptr) {
        rules[rule_pos].first.push_back(rule);
        rules[rule_pos].second = rule.associativity;
        return;
    }
    if (!rule.associativity->equals(rules[rule_pos].second)) {
        throw Error{"rules with precedence '" + rule.precedence->to_string()
                    + "' have different associativity: "
                    + rules[rule_pos].second->to_string()};
    }
    rules[rule_pos].first.push_back(rule);
}

Object* Parser::parse_associated(Vector* args) {
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{"failed to parse. Second argument is not an 'Integer'"};
    }
    auto associated{rules.at(precedence->int_value())};
    for (const auto& rule : associated.first) {
        if (rule.predicate->call(args)->equals(new Boolean{true})) {
            return rule.expression->call(args);
        }
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{"failed to parse. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{"failed to parse. Fourth argument is not an 'Integer'"};
    }
    Object* obj{objs->get(pos)};
    if (associated.second->string_value() == "right_to_left") {
        pos = new Integer{pos->int_value() - 1};
    } else {
        pos = new Integer{pos->int_value() + 1};
    }
    args->set(args_pos_pos, pos);
    return obj;
}

Object* Parser::parse_objs(Vector* objs) {
    auto precedence{new Integer{0}};
    auto pos{new Integer{0}};
    auto count{rules.size()};
    Vector* args{new Vector};
    args->push_back(this);
    args->push_back(precedence);
    args->push_back(objs);
    args->push_back(pos);
    while (static_cast<std::size_t>(precedence->int_value()) < count) {
        if (rules[precedence->int_value()].second == nullptr) {
            precedence = new Integer{precedence->int_value() + 1};
            args->set(args_precedence_pos, precedence);
            continue;
        }
        if (rules[precedence->int_value()].second->string_value()
            == "left_to_right") {
            pos = new Integer{0};
            args->set(args_pos_pos, pos);
            while (static_cast<std::size_t>(pos->int_value()) < objs->size()) {
                parse_associated(args);
                pos = dynamic_cast<Integer*>(args->get(args_pos_pos));
            }
        } else {
            pos = new Integer{static_cast<int>(objs->size() - 1)};
            args->set(args_pos_pos, pos);
            while (pos->int_value() >= 0) {
                parse_associated(args);
                pos = dynamic_cast<Integer*>(args->get(args_pos_pos));
            }
        }
        precedence = new Integer{precedence->int_value() + 1};
        args->set(args_precedence_pos, precedence);
    }
    return objs;
}

Object* Parser::parse(const std::string& str) {
    std::size_t pos{0};
    std::size_t length{str.length()};
    Vector* objs{new Vector};
    while (pos < length) {
        objs->push_back(next_atom(str, pos));
    }
    parse_objs(objs);
    if (objs->size() > 1) {
        throw Error{"multiple structures appear"};
    }
    return objs->at(0);
}

bool Parser::is_punctuation(int ch) const {
    return (std::ispunct(ch) && ch != '_') || std::isspace(ch);
}

Number* Parser::next_number(const std::string& str, std::size_t& pos) const {
    std::stringstream ss{str.substr(pos) + ' '};
    double float_num{0};
    ss >> float_num;
    pos += ss.tellg();
    auto int_num{static_cast<std::int64_t>(float_num)};
    if (float_num == int_num) {
        return new Integer{int_num};
    }
    return new Float{float_num};
}

String* Parser::next_string(const std::string& str, std::size_t& pos) const {
    std::size_t start{++pos};
    std::size_t end{str.length()};
    std::string s;
    while (pos < end) {
        if (str[pos] == '\\') {
            switch (str[++pos]) {
            case '"':
                s.push_back('"');
                break;
            case '\\':
                s.push_back('\\');
                break;
            case 'b':
                s.push_back('\b');
                break;
            case 'f':
                s.push_back('\f');
                break;
            case 'n':
                s.push_back('\n');
                break;
            case 'r':
                s.push_back('\r');
                break;
            case 't':
                s.push_back('\t');
                break;
            }
            ++pos;
            continue;
        }
        if (str[pos] == '"') {
            ++pos;
            return new String{s};
        }
        s.push_back(str[pos]);
        ++pos;
    }
    throw Error{"unterminated 'String'"};
}

Symbol* Parser::next_symbol(const std::string& str, std::size_t& pos) const {
    if (is_punctuation(str[pos])) {
        return new Symbol{{str[pos++]}};
    }
    std::size_t start{pos};
    std::size_t end{str.length()};
    while (!is_punctuation(str[pos]) && pos < end) {
        ++pos;
    }
    return new Symbol{str.substr(start, pos - start)};
}

Object* Parser::next_atom(const std::string& str, std::size_t& pos) const {
    while (std::isspace(str[pos])) {
        ++pos;
    }
    if (str[pos] == '"') {
        return next_string(str, pos);
    }
    if (std::isdigit(str[pos])) {
        return next_number(str, pos);
    }
    auto symbol{next_symbol(str, pos)};
    if (symbol->string_value() == "null") {
        return new Null;
    }
    if (symbol->string_value() == "true") {
        return new Boolean{true};
    }
    if (symbol->string_value() == "false") {
        return new Boolean{false};
    }
    return symbol;
}

Object* Parser::is_vector(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    return new Boolean{objs->get(pos)->equals(new Symbol{"["})};
}

Object* Parser::is_set(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{"failed to parse 'Set'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Set'. Fourth argument is not an 'Integer'"};
    }
    return new Boolean{objs->get(pos)->equals(new Symbol{"{"})};
}

Object* Parser::is_list(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{"failed to parse 'List'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'List'. Fourth argument is not an 'Integer'"};
    }
    return new Boolean{objs->get(pos)->equals(new Symbol{"("})};
}

Object* Parser::is_quote(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Quote'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Quote'. Fourth argument is not an 'Integer'"};
    }
    return new Boolean{objs->get(pos)->equals(new Symbol{"'"})};
}

Object* Parser::is_getter(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Getter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Getter'. Fourth argument is not an 'Integer'"};
    }
    return new Boolean{objs->get(pos)->equals(new Symbol{"."})};
}

Object* Parser::is_setter(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Fourth argument is not an 'Integer'"};
    }
    return new Boolean{objs->get(pos)->equals(new Symbol{":"})};
}

Object* Parser::parse_vector(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(args_parser_pos))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Vector'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    auto start{pos->int_value()};
    pos = new Integer{pos->int_value() + 1};
    args->set(args_pos_pos, pos);
    auto vec{new Vector};
    auto size{objs->size()};
    while (static_cast<std::size_t>(pos->int_value()) < size) {
        Object* obj{parser->parse_associated(args)};
        pos = dynamic_cast<Integer*>(args->get(args_pos_pos));
        if (obj->equals(new Symbol{"]"})) {
            pos = new Integer{pos->int_value() - 1};
            while (pos->int_value() > start) {
                objs->erase(pos->int_value());
                pos = new Integer{pos->int_value() - 1};
            }
            pos = new Integer{pos->int_value() + 1};
            args->set(args_pos_pos, pos);
            parser->parse_objs(vec);
            std::size_t i{0};
            while (i < vec->size()) {
                if (vec->at(i)->equals(new Symbol{","})) {
                    vec->erase(i);
                    continue;
                }
                ++i;
            }
            objs->at(start) = vec;
            return vec;
        }
        vec->push_back(obj);
    }
    throw Error{"unterminated 'Vector'"};
}

Object* Parser::parse_set(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(args_parser_pos))};
    if (parser == nullptr) {
        throw Error{"failed to parse 'Set'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Set'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{"failed to parse 'Set'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Set'. Fourth argument is not an 'Integer'"};
    }
    auto start{pos->int_value()};
    pos = new Integer{pos->int_value() + 1};
    args->set(args_pos_pos, pos);
    auto vec{new Vector};
    auto size{objs->size()};
    while (static_cast<std::size_t>(pos->int_value()) < size) {
        Object* obj{parser->parse_associated(args)};
        pos = dynamic_cast<Integer*>(args->get(args_pos_pos));
        if (obj->equals(new Symbol{"}"})) {
            pos = new Integer{pos->int_value() - 1};
            while (pos->int_value() > start) {
                objs->erase(pos->int_value());
                pos = new Integer{pos->int_value() - 1};
            }
            pos = new Integer{pos->int_value() + 1};
            args->set(args_pos_pos, pos);
            parser->parse_objs(vec);
            std::size_t i{0};
            while (i < vec->size()) {
                if (vec->at(i)->equals(new Symbol{","})) {
                    vec->erase(i);
                    continue;
                }
                ++i;
            }
            auto set{new Set};
            for (std::size_t i{0}, length{vec->size()}; i < length; ++i) {
                set->insert(vec->at(i));
            }
            objs->at(start) = set;
            return set;
        }
        vec->push_back(obj);
    }
    throw Error{"unterminated 'Set'"};
}

Object* Parser::parse_list(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(args_parser_pos))};
    if (parser == nullptr) {
        throw Error{"failed to parse 'List'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'List'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{"failed to parse 'List'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'List'. Fourth argument is not an 'Integer'"};
    }
    auto start{pos->int_value()};
    pos = new Integer{pos->int_value() + 1};
    args->set(args_pos_pos, pos);
    auto vec{new Vector};
    auto size{objs->size()};
    while (static_cast<std::size_t>(pos->int_value()) < size) {
        Object* obj{parser->parse_associated(args)};
        pos = dynamic_cast<Integer*>(args->get(args_pos_pos));
        if (obj->equals(new Symbol{")"})) {
            pos = new Integer{pos->int_value() - 1};
            while (pos->int_value() > start) {
                objs->erase(pos->int_value());
                pos = new Integer{pos->int_value() - 1};
            }
            pos = new Integer{pos->int_value() + 1};
            args->set(args_pos_pos, pos);
            parser->parse_objs(vec);
            std::size_t i{0};
            while (i < vec->size()) {
                if (vec->at(i)->equals(new Symbol{","})) {
                    vec->erase(i);
                    continue;
                }
                ++i;
            }
            auto lst{new List};
            for (std::size_t i{0}, length{vec->size()}; i < length; ++i) {
                lst->push_back(vec->at(i));
            }
            objs->at(start) = lst;
            return lst;
        }
        vec->push_back(obj);
    }
    throw Error{"unterminated 'List'"};
}

Object* Parser::parse_quote(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(args_parser_pos))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Quote'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Quote'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Quote'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Quote'. Fourth argument is not an 'Integer'"};
    }
    auto quoted_pos{pos->int_value() + 1};
    auto quote{new Quote{objs->at(quoted_pos)}};
    objs->erase(quoted_pos);
    objs->set(pos, quote);
    return quote;
}

Object* Parser::parse_getter(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(args_parser_pos))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Getter'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Getter'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Getter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Getter'. Fourth argument is not an 'Integer'"};
    }
    auto key_pos{pos->int_value() - 1};
    auto value_pos{pos->int_value() + 1};
    auto getter{
        new Getter{objs->at(key_pos), objs->at(value_pos)}
    };
    objs->erase(value_pos);
    objs->erase(pos->int_value());
    pos = new Integer{key_pos};
    args->set(args_pos_pos, pos);
    objs->set(pos, getter);
    return getter;
}

Object* Parser::parse_setter(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->get(args_parser_pos))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Setter'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->get(args_precedence_pos))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->get(args_objs_pos))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->get(args_pos_pos))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Fourth argument is not an 'Integer'"};
    }
    auto key_pos{pos->int_value() - 1};
    auto value_pos{pos->int_value() + 1};
    auto setter{
        new Setter{objs->at(key_pos), objs->at(value_pos)}
    };
    objs->erase(value_pos);
    objs->erase(pos->int_value());
    pos = new Integer{key_pos};
    args->set(args_pos_pos, pos);
    objs->set(pos, setter);
    return setter;
}

}
