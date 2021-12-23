#ifndef FUNDOT_CORE_VECTOR_H
#define FUNDOT_CORE_VECTOR_H

#include "object.h"
#include <vector>

namespace fundot {

class Vector : public Object {
public:
    void trace() override;

    bool equals(const Object* obj) const override;

    std::string to_string() const override;

    Object* eval() override;

    Object*& at(std::size_t pos);

    bool empty() const;

    std::size_t size() const;

    std::size_t erase(std::size_t pos);

    void push_back(Object* obj);

private:
    std::vector<Object*> raw_vec;
};

}

#endif
