#include "quote.h"

namespace fundot {

Quote::Quote(Object* expr) : expr(expr) {
}

void Quote::trace() {
    Object::trace();
    expr->trace();
}

std::string Quote::to_string() const {
    return "'" + expr->to_string();
}

Object* Quote::eval() {
    return expr;
}

Object* Quote::quote(std::size_t count) {
    return new Quote{expr->quote(count)};
}

Object*& Quote::quoted() {
    return expr;
}

Object* const& Quote::quoted() const {
    return expr;
}

Unquote::Unquote(Object* expr) : Quote(expr) {
}

std::string Unquote::to_string() const {
    return "~" + quoted()->to_string();
}

Object* Unquote::eval() {
    throw Error{"evaluating 'Unquote' outside 'SyntaxQuote'"};
}

Object* Unquote::quote(std::size_t count) {
    if (count == 0) {
        return quoted()->eval();
    }
    return quoted()->quote(count - 1);
}

SyntaxQuote::SyntaxQuote(Object* expr) : Quote(expr) {
}

std::string SyntaxQuote::to_string() const {
    return "`" + quoted()->to_string();
}

Object* SyntaxQuote::eval() {
    return quoted()->quote(0);
}

Object* SyntaxQuote::quote(std::size_t count) {
    return quoted()->quote(count + 1);
}

}
