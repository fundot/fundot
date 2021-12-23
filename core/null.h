#ifndef FUNDOT_CORE_NULL_H
#define FUNDOT_CORE_NULL_H

#include "object.h"

namespace fundot {

class Null : public Object {
public:
    std::string to_string() const override;
};

}

#endif
