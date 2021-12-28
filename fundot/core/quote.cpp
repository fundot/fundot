#include "quote.h"

namespace fundot {

Quote::Quote(Object* expr) : expr(expr) {
}

void Quote::traverse(const Visitor& visit) {
    visit(expr);
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

SyntaxQuote::SyntaxQuote(Object* expr) : Quote(expr) {
}

std::string SyntaxQuote::to_string() const {
    return "`" + quoted()->to_string();
}

Object* SyntaxQuote::eval() {
    quoted()->traverse(eval_unquote);
    return quoted();
}

void SyntaxQuote::eval_unquote(Object*& obj) {
    auto unquote{dynamic_cast<Unquote*>(obj)};
    if (unquote != nullptr) {
        obj = unquote->quoted()->eval();
    }
    obj->traverse(eval_unquote);
}

}
