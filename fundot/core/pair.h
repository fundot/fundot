#ifndef FUNDOT_CORE_PAIR_H
#define FUNDOT_CORE_PAIR_H

#include "number.h"
#include <utility>

namespace fundot {

class Pair : public Object {
public:
    Pair(Object* first, Object* second);

    void traverse(const Visitor& visit) override;

    void trace() override;

    bool equals(const Object* obj) const override;

    Object* get(Object* obj) const override;

    Object* set(Object* index, Object* value) override;

    Object*& first();

    Object* const& first() const;

    Object*& second();

    Object* const& second() const;

private:
    std::pair<Object*, Object*> raw_pair;
};

class Getter : public Pair {
public:
    Getter(Object* first, Object* second);

    std::string to_string() const override;

    Object* eval() override;
};

class Setter : public Pair {
public:
    Setter(Object* first, Object* second);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    Object* eval() override;
};

}

#endif
