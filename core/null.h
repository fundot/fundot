#ifndef FUNDOT_CORE_NULL_H
#define FUNDOT_CORE_NULL_H

#include "object.h"

namespace fundot {

class Null : public Object {
public:
    bool equals(const Object* obj) const override;

    std::string to_string() const override;
};

}

#endif
