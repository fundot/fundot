#include "fundot/fundot.h"

namespace fundot {

class Reader::Impl {
public:
    std::istream& read(Object& object, std::istream& is) const;
};

std::list<Object>::iterator findUnaryOperator(std::list<Object>& list)
{
    static std::unordered_set<Object, Hasher> binary_operators = {
        {Symbol({"."})},  {Symbol({"*"})},  {Symbol({"/"})},  {Symbol({"%"})},
        {Symbol({"+"})},  {Symbol({"-"})},  {Symbol({"<<"})}, {Symbol({">>"})},
        {Symbol({"<"})},  {Symbol({">"})},  {Symbol({"<="})}, {Symbol({">="})},
        {Symbol({"=="})}, {Symbol({"!="})}, {Symbol({"&"})},  {Symbol({"^"})},
        {Symbol({"|"})},  {Symbol({"&&"})}, {Symbol({"||"})}, {Symbol({"="})},
        {Symbol({":"})}};
    static std::list<Symbol> unary_operators = {{"+"}, {"-"}, {"!"}, {"~"}};
    for (const auto& symbol : unary_operators) {
        auto iter = std::find(list.begin(), list.end(), Object({symbol}));
        if (iter != list.end()) {
            if (iter == list.begin()) {
                return iter;
            }
            if (binary_operators.find(*--iter) != binary_operators.end()) {
                return ++iter;
            }
        }
    }
    return list.end();
}

void parseUnaryOperator(std::list<Object>& list)
{
    auto iter = findUnaryOperator(list);
    while (iter != list.end()) {
        if (*iter == Object({Symbol({"+"})})) {
            auto next = iter;
            if (++next == list.end()) {
                throw std::runtime_error("Unexpected operator.");
            }
            list.erase(iter);
        }
        else if (*iter == Object({Symbol({"-"})})) {
            auto next = iter;
            if (++next == list.end()) {
                throw std::runtime_error("Unexpected operator.");
            }
            *iter = {Negator({*next})};
            list.erase(next);
        }
        else if (*iter == Object({Symbol({"!"})})) {
            auto next = iter;
            if (++next == list.end()) {
                throw std::runtime_error("Unexpected operator.");
            }
            *iter = {Not({*next})};
            list.erase(next);
        }
        else if (*iter == Object({Symbol({"~"})})) {
            auto next = iter;
            if (++next == list.end()) {
                throw std::runtime_error("Unexpected operator.");
            }
            *iter = {BitwiseNot({*next})};
            list.erase(next);
        }
        iter = findUnaryOperator(list);
    }
}

Object buildBinaryOperator(const Symbol& symbol,
                           const std::pair<Object, Object>& pair)
{
    if (symbol.value == ":") {
        return {Setter({pair})};
    }
    if (symbol.value == "=") {
        return {Assignment({pair})};
    }
    if (symbol.value == ".") {
        return {Getter({pair})};
    }
    if (symbol.value == "+") {
        return {Adder({pair})};
    }
    if (symbol.value == "-") {
        return {Subtractor({pair})};
    }
    if (symbol.value == "*") {
        return {Multiplier({pair})};
    }
    if (symbol.value == "/") {
        return {Divisor({pair})};
    }
    if (symbol.value == "%") {
        return {Modular({pair})};
    }
    if (symbol.value == "<") {
        return {Less({pair})};
    }
    if (symbol.value == ">") {
        return {Greater({pair})};
    }
    if (symbol.value == "<=") {
        return {LessEqual({pair})};
    }
    if (symbol.value == ">=") {
        return {GreaterEqual({pair})};
    }
    if (symbol.value == "==") {
        return {EqualTo({pair})};
    }
    if (symbol.value == "!=") {
        return {NotEqualTo({pair})};
    }
    if (symbol.value == "&&") {
        return {And({pair})};
    }
    if (symbol.value == "||") {
        return {Or({pair})};
    }
    if (symbol.value == "&") {
        return {BitwiseAnd({pair})};
    }
    if (symbol.value == "|") {
        return {BitwiseOr({pair})};
    }
    if (symbol.value == "^") {
        return {BitwiseXor({pair})};
    }
    if (symbol.value == "<<") {
        return {LeftShift({pair})};
    }
    if (symbol.value == ">>") {
        return {RightShift({pair})};
    }
    return {};
}

void parseBinaryOperator(std::list<Object>& list)
{
    static std::list<Symbol> left_to_right_operators = {
        {"."},  {"*"}, {"/"}, {"%"},  {"+"},  {"-"},  {"<<"},
        {">>"}, {"<"}, {">"}, {"<="}, {">="}, {"=="}, {"!="},
        {"&"},  {"^"}, {"|"}, {"&&"}, {"||"}};
    for (const auto& symbol : left_to_right_operators) {
        Object to_find({symbol});
        auto iter = std::find(list.begin(), list.end(), to_find);
        while (iter != list.end()) {
            if (iter == --list.end() || iter == list.begin()) {
                throw std::runtime_error("Unexpected operator.");
            }
            auto prev = iter;
            auto next = iter;
            --prev;
            ++next;
            std::pair<Object, Object> pair(*prev, *next);
            *iter = buildBinaryOperator(symbol, pair);
            list.erase(next);
            list.erase(prev);
            iter = std::find(list.begin(), list.end(), to_find);
        }
    }
    static std::list<Symbol> right_to_left_operators = {{"="}, {":"}};
    for (const auto& symbol : right_to_left_operators) {
        Object to_find({symbol});
        auto iter = std::find(list.rbegin(), list.rend(), to_find);
        while (iter != list.rend()) {
            if (iter == --list.rend() || iter == list.rbegin()) {
                throw std::runtime_error("Unexpected operator.");
            }
            auto prev = --iter.base();
            auto next = --iter.base();
            --prev;
            ++next;
            std::pair<Object, Object> pair(*prev, *next);
            *iter = buildBinaryOperator(symbol, pair);
            list.erase(next);
            list.erase(prev);
            iter = std::find(list.rbegin(), list.rend(), to_find);
        }
    }
}

void parse(std::list<Object>& list)
{
    parseUnaryOperator(list);
    parseBinaryOperator(list);
}

std::istream& operator>>(std::istream& is, String& string)
{
    std::string& value = string.value;
    value.clear();
    char c;
    is >> std::noskipws;
    while (is >> c) {
        if (c == '"') {
            break;
        }
        value.push_back(c);
    }
    is >> std::skipws;
    return is;
}

std::istream& operator>>(std::istream& is, Symbol& symbol)
{
    static std::unordered_set<char> delimiters = {
        ';',  ')',  ']',  '}',  ',', '"', '\'', ':', '.', ' ', '\n',
        '\t', '\v', '\f', '\r', '(', '[', '{',  '+', '-', '*', '/',
        '%',  '<',  '>',  '=',  '&', '|', '^',  '~', '!'};
    std::string& value = symbol.value;
    value.clear();
    char c;
    is >> c;
    if (c == '=' || c == '!') {
        value.push_back(c);
        is >> c;
        if (c == '=') {
            value.push_back(c);
            return is;
        }
        is.putback(c);
        return is;
    }
    if (c == '<' || c == '>') {
        value.push_back(c);
        char ch;
        is >> ch;
        if (ch == c || ch == '=') {
            value.push_back(ch);
            return is;
        }
        is.putback(ch);
        return is;
    }
    if (c == '&' || c == '|') {
        value.push_back(c);
        char ch;
        is >> ch;
        if (ch == c) {
            value.push_back(ch);
            return is;
        }
        is.putback(ch);
        return is;
    }
    if (delimiters.find(c) != delimiters.end()) {
        value.push_back(c);
        return is;
    }
    is.putback(c);
    is >> std::noskipws;
    while (is >> c) {
        if (delimiters.find(c) != delimiters.end()) {
            is.putback(c);
            break;
        }
        value.push_back(c);
    }
    is >> std::skipws;
    return is;
}

std::istream& operator>>(std::istream& is, List& list)
{
    auto& value = list.value;
    value.clear();
    char c;
    is >> c;
    if (c == ';') {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        is >> c;
    }
    if (c == ')') {
        return is;
    }
    is.putback(c);
    Object elem;
    while (is >> elem) {
        value.push_back(elem);
        is >> c;
        if (c == ';') {
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            is >> c;
        }
        if (c == ')') {
            parse(value);
            return is;
        }
        is.putback(c);
    }
    return is;
}

std::istream& operator>>(std::istream& is, Vector& vector)
{
    auto& value = vector.value;
    value.clear();
    char c;
    is >> c;
    if (c == ';') {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        is >> c;
    }
    if (c == ']') {
        return is;
    }
    is.putback(c);
    Object elem;
    for (;;) {
        std::list<Object> list;
        while (is >> elem) {
            list.push_back(elem);
            is >> c;
            if (c == ';') {
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                is >> c;
            }
            if (c == ',') {
                break;
            }
            if (c == ']') {
                is.putback(c);
                break;
            }
            is.putback(c);
        }
        parse(list);
        if (list.empty() == false) {
            value.push_back(list.front());
        }
        is >> c;
        if (c == ']') {
            return is;
        }
        is.putback(c);
    }
    return is;
}

std::istream& operator>>(std::istream& is, UnorderedSet& set)
{
    auto& value = set.value;
    value.clear();
    char c;
    is >> c;
    if (c == ';') {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        is >> c;
    }
    if (c == '}') {
        return is;
    }
    is.putback(c);
    Object elem;
    for (;;) {
        std::list<Object> list;
        while (is >> elem) {
            list.push_back(elem);
            is >> c;
            if (c == ';') {
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                is >> c;
            }
            if (c == ',') {
                break;
            }
            if (c == '}') {
                is.putback(c);
                break;
            }
            is.putback(c);
        }
        parse(list);
        if (list.empty() == false) {
            value.emplace(list.front());
        }
        is >> c;
        if (c == '}') {
            return is;
        }
        is.putback(c);
    }
    return is;
}

std::istream& operator>>(std::istream& is, Object& object)
{
    char c;
    is >> c;
    if (c == ';') {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        is >> c;
    }
    if (c == '\'') {
        Quote quote;
        is >> quote.value;
        object.value = quote;
        return is;
    }
    if (c == '"') {
        String string;
        is >> string;
        object.value = string;
        return is;
    }
    if (c == '(') {
        List list;
        is >> list;
        object.value = list;
        return is;
    }
    if (c == '[') {
        Vector vector;
        is >> vector;
        object.value = vector;
        return is;
    }
    if (c == '{') {
        UnorderedSet set;
        is >> set;
        object.value = set;
        return is;
    }
    if (std::isdigit(c)) {
        is.putback(c);
        Float num;
        is >> num.value;
        if (static_cast<std::int64_t>(num.value) != num.value) {
            object.value = num;
            return is;
        }
        object.value = Integer({static_cast<std::int64_t>(num.value)});
        return is;
    }
    is.putback(c);
    Symbol symbol;
    is >> symbol;
    if (symbol.value == "null") {
        object.value = Null();
        return is;
    }
    if (symbol.value == "true") {
        object.value = Boolean({true});
        return is;
    }
    if (symbol.value == "false") {
        object.value = Boolean({false});
        return is;
    }
    object.value = symbol;
    return is;
}

std::istream& Reader::Impl::read(Object& object, std::istream& is) const
{
    std::list<Object> list;
    char c;
    Object elem;
    while (is >> elem) {
        list.push_back(elem);
        is >> std::noskipws >> c;
        while (std::iswspace(c) && c != '\n') {
            is >> c;
        }
        is >> std::skipws;
        if (c == ';') {
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (c == '\n' || is.eof() || c == ';') {
            parse(list);
            object = list.back();
            return is;
        }
        is.putback(c);
    }
    return is;
}

std::istream& Reader::operator()(Object& object, std::istream& is) const
{
    return pimpl_->read(object, is);
}

Reader::Reader() : pimpl_(new Impl) {}

Reader::~Reader() = default;

}  // namespace fundot
