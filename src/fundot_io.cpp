#include "fundot_io.h"

namespace fundot {

std::list<Object>::iterator findUnaryOperator(std::list<Object>& list)
{
    static std::unordered_set<Object, Hash<Object>> binary_operators = {
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
            list.erase(iter);
        }
        else if (*iter == Object({Symbol({"-"})})) {
            auto next = iter;
            ++next;
            *iter = {Negator({*next})};
            list.erase(next);
        }
        else if (*iter == Object({Symbol({"!"})})) {
            auto next = iter;
            ++next;
            *iter = {Not({*next})};
            list.erase(next);
        }
        else if (*iter == Object({Symbol({"~"})})) {
            auto next = iter;
            ++next;
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
        return {Setter({pair})};
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
    static std::list<Symbol> operators = {
        {"."},  {"*"}, {"/"}, {"%"},  {"+"},  {"-"},  {"<<"},
        {">>"}, {"<"}, {">"}, {"<="}, {">="}, {"=="}, {"!="},
        {"&"},  {"^"}, {"|"}, {"&&"}, {"||"}, {"="},  {":"}};
    for (const auto& symbol : operators) {
        Object to_find({symbol});
        auto iter = std::find(list.begin(), list.end(), to_find);
        while (iter != list.end()) {
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
        ')',  ']',  '}',  ',',  '"', '\'', ':', '.', ' ', '\n',
        '\t', '\v', '\f', '\r', '(', '[',  '{', '+', '-', '*',
        '/',  '%',  '<',  '>',  '=', '&',  '|', '^', '~', '!'};
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
    if (c == ')') {
        return is;
    }
    is.putback(c);
    Object elem;
    while (is >> elem) {
        value.push_back(elem);
        is >> c;
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

std::ostream& operator<<(std::ostream& os, const Boolean& boolean)
{
    return os << std::boolalpha << boolean.value << std::noboolalpha;
}

std::ostream& operator<<(std::ostream& os, const Integer& num)
{
    return os << num.value;
}

std::ostream& operator<<(std::ostream& os, const Float& num)
{
    return os << num.value;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    return os << '"' << string.value << '"';
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol)
{
    return os << symbol.value;
}

std::ostream& operator<<(std::ostream& os, const List& list)
{
    if (list.value.empty()) {
        return os << "()";
    }
    os << '(';
    for (const auto& object : list.value) {
        os << object << ' ';
    }
    return os << "\b)";
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    if (vector.value.empty()) {
        return os << "[]";
    }
    os << '[';
    for (const auto& object : vector.value) {
        os << object << ", ";
    }
    return os << "\b\b]";
}

std::ostream& operator<<(std::ostream& os, const UnorderedSet& set)
{
    if (set.value.empty()) {
        return os << "{}";
    }
    os << '{';
    for (const auto& object : set.value) {
        os << object << ", ";
    }
    return os << "\b\b}";
}

std::ostream& operator<<(std::ostream& os, const Setter& setter)
{
    return os << setter.value.first << " : " << setter.value.second;
}

std::ostream& operator<<(std::ostream& os, const Getter& getter)
{
    return os << getter.value.first << '.' << getter.value.second;
}

std::ostream& operator<<(std::ostream& os, const Adder& adder)
{
    return os << adder.value.first << " + " << adder.value.second;
}

std::ostream& operator<<(std::ostream& os, const Subtractor& subtractor)
{
    return os << subtractor.value.first << " - " << subtractor.value.second;
}

std::ostream& operator<<(std::ostream& os, const Multiplier& multiplier)
{
    return os << multiplier.value.first << " * " << multiplier.value.second;
}

std::ostream& operator<<(std::ostream& os, const Divisor& divisor)
{
    return os << divisor.value.first << " / " << divisor.value.second;
}

std::ostream& operator<<(std::ostream& os, const Modular& modular)
{
    return os << modular.value.first << " % " << modular.value.second;
}

std::ostream& operator<<(std::ostream& os, const Less& less)
{
    return os << less.value.first << " < " << less.value.second;
}

std::ostream& operator<<(std::ostream& os, const Greater& greater)
{
    return os << greater.value.first << " > " << greater.value.second;
}

std::ostream& operator<<(std::ostream& os, const LessEqual& less_equal)
{
    return os << less_equal.value.first << " <= " << less_equal.value.second;
}

std::ostream& operator<<(std::ostream& os, const GreaterEqual& greater_equal)
{
    return os << greater_equal.value.first
              << " >= " << greater_equal.value.second;
}

std::ostream& operator<<(std::ostream& os, const EqualTo& equal_to)
{
    return os << equal_to.value.first << " == " << equal_to.value.second;
}

std::ostream& operator<<(std::ostream& os, const Quote& quote)
{
    return os << '\'' << quote.value;
}

std::ostream& operator<<(std::ostream& os, const Negator& negator)
{
    return os << '-' << negator.value;
}

std::ostream& operator<<(std::ostream& os, const And& logical_and)
{
    return os << logical_and.value.first << " && " << logical_and.value.second;
}

std::ostream& operator<<(std::ostream& os, const Or& logical_or)
{
    return os << logical_or.value.first << " || " << logical_or.value.second;
}

std::ostream& operator<<(std::ostream& os, const Not& logical_not)
{
    return os << '!' << logical_not.value;
}

std::ostream& operator<<(std::ostream& os, const BitwiseAnd& bitwise_and)
{
    return os << bitwise_and.value.first << " & " << bitwise_and.value.second;
}

std::ostream& operator<<(std::ostream& os, const BitwiseOr& bitwise_or)
{
    return os << bitwise_or.value.first << " | " << bitwise_or.value.second;
}

std::ostream& operator<<(std::ostream& os, const BitwiseXor& bitwise_xor)
{
    return os << bitwise_xor.value.first << " ^ " << bitwise_xor.value.second;
}

std::ostream& operator<<(std::ostream& os, const BitwiseNot& bitwise_not)
{
    return os << '~' << bitwise_not.value;
}

std::ostream& operator<<(std::ostream& os, const LeftShift& left_shift)
{
    return os << left_shift.value.first << " << " << left_shift.value.second;
}

std::ostream& operator<<(std::ostream& os, const RightShift& right_shift)
{
    return os << right_shift.value.first << " >> " << right_shift.value.second;
}

std::ostream& operator<<(std::ostream& os, const Object& object)
{
    const auto& value = object.value;
    if (value.type() == typeid(Boolean)) {
        return os << std::any_cast<const Boolean&>(value);
    }
    if (value.type() == typeid(Integer)) {
        return os << std::any_cast<const Integer&>(value);
    }
    if (value.type() == typeid(Float)) {
        return os << std::any_cast<const Float&>(value);
    }
    if (value.type() == typeid(String)) {
        return os << std::any_cast<const String&>(value);
    }
    if (value.type() == typeid(Symbol)) {
        return os << std::any_cast<const Symbol&>(value);
    }
    if (value.type() == typeid(List)) {
        return os << std::any_cast<const List&>(value);
    }
    if (value.type() == typeid(Vector)) {
        return os << std::any_cast<const Vector&>(value);
    }
    if (value.type() == typeid(UnorderedSet)) {
        return os << std::any_cast<const UnorderedSet&>(value);
    }
    if (value.type() == typeid(Setter)) {
        return os << std::any_cast<const Setter&>(value);
    }
    if (value.type() == typeid(Getter)) {
        return os << std::any_cast<const Getter&>(value);
    }
    if (value.type() == typeid(Adder)) {
        return os << std::any_cast<const Adder&>(value);
    }
    if (value.type() == typeid(Subtractor)) {
        return os << std::any_cast<const Subtractor&>(value);
    }
    if (value.type() == typeid(Multiplier)) {
        return os << std::any_cast<const Multiplier&>(value);
    }
    if (value.type() == typeid(Divisor)) {
        return os << std::any_cast<const Divisor&>(value);
    }
    if (value.type() == typeid(Modular)) {
        return os << std::any_cast<const Modular&>(value);
    }
    if (value.type() == typeid(Less)) {
        return os << std::any_cast<const Less&>(value);
    }
    if (value.type() == typeid(Greater)) {
        return os << std::any_cast<const Greater&>(value);
    }
    if (value.type() == typeid(LessEqual)) {
        return os << std::any_cast<const LessEqual&>(value);
    }
    if (value.type() == typeid(GreaterEqual)) {
        return os << std::any_cast<const GreaterEqual&>(value);
    }
    if (value.type() == typeid(EqualTo)) {
        return os << std::any_cast<const EqualTo&>(value);
    }
    if (value.type() == typeid(Quote)) {
        return os << std::any_cast<const Quote&>(value);
    }
    if (value.type() == typeid(Negator)) {
        return os << std::any_cast<const Negator&>(value);
    }
    if (value.type() == typeid(Null)) {
        return os << "null";
    }
    if (value.type() == typeid(And)) {
        return os << std::any_cast<const And&>(value);
    }
    if (value.type() == typeid(Or)) {
        return os << std::any_cast<const Or&>(value);
    }
    if (value.type() == typeid(Not)) {
        return os << std::any_cast<const Not&>(value);
    }
    if (value.type() == typeid(BitwiseAnd)) {
        return os << std::any_cast<const BitwiseAnd&>(value);
    }
    if (value.type() == typeid(BitwiseOr)) {
        return os << std::any_cast<const BitwiseOr&>(value);
    }
    if (value.type() == typeid(BitwiseXor)) {
        return os << std::any_cast<const BitwiseXor&>(value);
    }
    if (value.type() == typeid(LeftShift)) {
        return os << std::any_cast<const LeftShift&>(value);
    }
    if (value.type() == typeid(RightShift)) {
        return os << std::any_cast<const RightShift&>(value);
    }
    if (value.type() == typeid(BitwiseNot)) {
        return os << std::any_cast<const BitwiseNot&>(value);
    }
    return os;
}

std::istream& Scanner::operator()(std::istream& is, Object& object) const
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
        if (c == '\n') {
            parse(list);
            object.value = List({list});
            return is;
        }
        is.putback(c);
    }
    return is;
}

}  // namespace fundot
