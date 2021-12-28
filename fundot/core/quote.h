#ifndef FUNDOT_CORE_QUOTE_H
#define FUNDOT_CORE_QUOTE_H

#include "object.h"

namespace fundot {

class Quote : public Object {
public:
    Quote(Object* expr);

    void traverse(const Visitor& visit) override;

    void trace() override;

    std::string to_string() const override;

    Object* eval() override;

    virtual Object*& quoted();

    virtual Object* const& quoted() const;

private:
    Object* expr;
};

class Unquote : public Quote {
public:
    Unquote(Object* expr);

    std::string to_string() const override;

    Object* eval() override;
};

class SyntaxQuote : public Quote {
public:
    SyntaxQuote(Object* expr);

    std::string to_string() const override;

    Object* eval() override;

private:
    static void eval_unquote(Object*& obj);
};

}

#endif
