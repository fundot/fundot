#ifndef FUNDOT_CORE_QUOTE_H
#define FUNDOT_CORE_QUOTE_H

#include "object.h"

namespace fundot {

class Quote : public Object {
public:
    Quote(Object* expr);

    void trace() override;

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;

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

    Object* quote(std::size_t count) override;
};

class SyntaxQuote : public Quote {
public:
    SyntaxQuote(Object* expr);

    std::string to_string() const override;

    Object* eval() override;

    Object* quote(std::size_t count) override;
};

}

#endif
