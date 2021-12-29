#ifndef FUNDOT_CORE_SET_H
#define FUNDOT_CORE_SET_H

#include "pair.h"
#include "symbol.h"
#include "vector.h"
#include <unordered_set>

namespace fundot {

class Set : public Object {
public:
    void trace() override;

    bool equals(const Object* obj) const override;

    std::string to_string() const override;

    Object* get(Object* obj) const override;

    Object* set(Object* index, Object* value) override;

    Object* call(Object* obj) override;

    Object* eval() override;

    Object* quote(std::size_t count) override;

    std::vector<Object*> to_vector() const;

    std::size_t size() const;

    void insert(Object* obj);

private:
    bool is_macro();

    bool is_function();

    Object* call_macro(Vector* args);

    Object* call_function(Vector* args);

    std::unordered_set<Object*, Object::Hash, Object::Equal> raw_set;
};

}

#endif
