#ifndef FUNDOT_CORE_LIST_H
#define FUNDOT_CORE_LIST_H

#include "null.h"
#include <list>

namespace fundot {

class List : public Object {
public:
    void trace() override;

    bool equals(const Object* obj) const override;

    std::string to_string() const override;

    Object* eval() override;

    void push_back(Object* obj);

private:
    std::list<Object*> raw_list;
};

}

#endif
