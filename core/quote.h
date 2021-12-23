#ifndef FUNDOT_CORE_QUOTE_H
#define FUNDOT_CORE_QUOTE_H

#include "object.h"

namespace fundot {

class Quote : public Object {
public:
    Quote(Object* quoted);

    Object* eval() override;

private:
    Object* quoted;
};

}

#endif
