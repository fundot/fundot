#ifndef FUNDOT_CORE_BOOLEAN_H
#define FUNDOT_CORE_BOOLEAN_H

#include "object.h"

namespace fundot {

class Boolean : public Object {
public:
    Boolean(bool raw_bool = false);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    bool bool_value() const;

private:
    bool raw_bool;
};

}

#endif
