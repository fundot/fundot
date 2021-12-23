#ifndef FUNDOT_CORE_SYMBOL_H
#define FUNDOT_CORE_SYMBOL_H

#include "object.h"

namespace fundot {

class Symbol : public Object {
public:
    Symbol(const std::string& raw_str);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    Object* eval() override;

private:
    std::string raw_str;
};

}

#endif
