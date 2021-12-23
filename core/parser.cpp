#include "parser.h"
#include <sstream>

namespace fundot {

Parser::Parser() {
    static auto left_to_right{new String{"left_to_right"}};
    static auto right_to_left{new String{"right_to_left"}};
    Rule vector_rule{new PrimitiveFunction{Parser::is_vector},
                     new PrimitiveFunction{Parser::parse_vector},
                     new Integer{0},
                     left_to_right};
    Rule set_rule{new PrimitiveFunction{Parser::is_set},
                  new PrimitiveFunction{Parser::parse_set},
                  new Integer{0},
                  left_to_right};
    Rule quote_rule{new PrimitiveFunction{Parser::is_quote},
                    new PrimitiveFunction{Parser::parse_quote},
                    new Integer{1},
                    left_to_right};
    Rule getter_rule{new PrimitiveFunction{Parser::is_getter},
                     new PrimitiveFunction{Parser::parse_getter},
                     new Integer{2},
                     left_to_right};
    Rule setter_rule{new PrimitiveFunction{Parser::is_setter},
                     new PrimitiveFunction{Parser::parse_setter},
                     new Integer{3},
                     right_to_left};
    rules.push_back({
        {vector_rule, set_rule},
        left_to_right
    });
    rules.push_back({{quote_rule}, left_to_right});
    rules.push_back({{getter_rule}, left_to_right});
    rules.push_back({{setter_rule}, right_to_left});
}

void Parser::trace() {
    Object::trace();
    for (auto& associated : rules) {
        associated.second->mark();
        for (auto& rule : associated.first) {
            rule.condition->mark();
            rule.consequence->mark();
            rule.precedence->mark();
            rule.associativity->mark();
        }
    }
}

Object* Parser::parse_associated(Vector* args) {
    auto precedence{dynamic_cast<Integer*>(args->at(1))};
    if (precedence == nullptr) {
        throw Error{"failed to parse. Second argument is not an 'Integer'"};
    }
    auto associated{rules.at(*precedence)};
    for (const auto& rule : associated.first) {
        if (rule.condition->call(args)->equals(new Boolean{true})) {
            return rule.consequence->call(args);
        }
    }
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{"failed to parse. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{"failed to parse. Fourth argument is not an 'Integer'"};
    }
    if (static_cast<const std::string&>(*associated.second)
        == "right_to_left") {
        return objs->at((*pos)--);
    }
    return objs->at((*pos)++);
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
    while (static_cast<std::size_t>(*precedence) < count) {
        if (static_cast<const std::string&>(*rules[*precedence].second)
            == "left_to_right") {
            static_cast<std::int64_t&>(*pos) = 0;
            while (static_cast<std::size_t>(*pos) < objs->size()) {
                parse_associated(args);
            }
        } else {
            static_cast<std::int64_t&>(*pos) = objs->size() - 1;
            while (*pos >= 0) {
                parse_associated(args);
            }
        }
        ++*precedence;
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
    while (pos < end) {
        if (str[pos] == '"') {
            return new String{str.substr(start, pos++ - start)};
        }
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
    return next_symbol(str, pos);
}

Object* Parser::is_vector(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    if (objs->at(*pos)->equals(new Symbol{"["})) {
        return new Boolean{true};
    }
    return new Boolean{false};
}

Object* Parser::is_set(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{"failed to parse 'Set'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Set'. Fourth argument is not an 'Integer'"};
    }
    if (objs->at(*pos)->equals(new Symbol{"{"})) {
        return new Boolean{true};
    }
    return new Boolean{false};
}

Object* Parser::is_quote(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Fourth argument is not an 'Integer'"};
    }
    if (objs->at(*pos)->equals(new Symbol{"'"})) {
        return new Boolean{true};
    }
    return new Boolean{false};
}

Object* Parser::is_getter(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Fourth argument is not an 'Integer'"};
    }
    if (objs->at(*pos)->equals(new Symbol{"."})) {
        return new Boolean{true};
    }
    return new Boolean{false};
}

Object* Parser::is_setter(Vector* args) {
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Setter'. Fourth argument is not an 'Integer'"};
    }
    if (objs->at(*pos)->equals(new Symbol{":"})) {
        return new Boolean{true};
    }
    return new Boolean{false};
}

Object* Parser::parse_vector(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->at(0))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Vector'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->at(1))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    auto start{*pos};
    ++*pos;
    auto vec{new Vector};
    auto size{objs->size()};
    while (static_cast<std::size_t>(*pos) < size) {
        Object* obj{parser->parse_associated(args)};
        if (obj->equals(new Symbol{"]"})) {
            while (--*pos > start) {
                objs->erase(*pos);
            }
            objs->at(start) = vec;
            ++*pos;
            parser->parse_objs(vec);
            return vec;
        }
        if (!obj->equals(new Symbol{","})) {
            vec->push_back(obj);
        }
    }
    throw Error{"unterminated 'Vector'"};
}

Object* Parser::parse_set(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->at(0))};
    if (parser == nullptr) {
        throw Error{"failed to parse 'Set'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->at(1))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Set'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{"failed to parse 'Set'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Set'. Fourth argument is not an 'Integer'"};
    }
    auto start{*pos};
    ++*pos;
    auto vec{new Vector};
    auto size{objs->size()};
    while (static_cast<std::size_t>(*pos) < size) {
        Object* obj{parser->parse_associated(args)};
        if (obj->equals(new Symbol{"}"})) {
            while (--*pos > start) {
                objs->erase(*pos);
            }
            ++*pos;
            parser->parse_objs(vec);
            auto set{new Set};
            for (std::size_t i{0}, length{vec->size()}; i < length; ++i) {
                set->insert(vec->at(i));
            }
            objs->at(start) = set;
            return set;
        }
        if (!obj->equals(new Symbol{","})) {
            vec->push_back(obj);
        }
    }
    throw Error{"unterminated 'Set'"};
}

Object* Parser::parse_quote(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->at(0))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Vector'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->at(1))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    auto quoted_pos{*pos + 1};
    auto quote{new Quote{objs->at(quoted_pos)}};
    objs->erase(quoted_pos);
    objs->at(*pos) = quote;
    return quote;
}

Object* Parser::parse_getter(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->at(0))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Vector'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->at(1))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    auto key_pos{*pos - 1};
    auto value_pos{*pos + 1};
    auto getter{
        new Getter{objs->at(key_pos), objs->at(value_pos)}
    };
    objs->erase(value_pos);
    objs->erase(*pos);
    objs->at(--*pos) = getter;
    return getter;
}

Object* Parser::parse_setter(Vector* args) {
    auto parser{dynamic_cast<Parser*>(args->at(0))};
    if (parser == nullptr) {
        throw Error{
            "failed to parse 'Vector'. First argument is not a 'Parser'"};
    }
    auto precedence{dynamic_cast<Integer*>(args->at(1))};
    if (precedence == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Second argument is not a 'Precedence'"};
    }
    auto objs{dynamic_cast<Vector*>(args->at(2))};
    if (objs == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Third argument is not a 'Vector'"};
    }
    auto pos{dynamic_cast<Integer*>(args->at(3))};
    if (pos == nullptr) {
        throw Error{
            "failed to parse 'Vector'. Fourth argument is not an 'Integer'"};
    }
    auto key_pos{*pos - 1};
    auto value_pos{*pos + 1};
    auto setter{
        new Setter{objs->at(key_pos), objs->at(value_pos)}
    };
    objs->erase(value_pos);
    objs->erase(*pos);
    objs->at(--*pos) = setter;
    return setter;
}

}
