#ifndef FUNDOT_CORE_NUMBER_H
#define FUNDOT_CORE_NUMBER_H

#include "object.h"
#include <cstdint>

namespace fundot {

class Number : public Object {
public:
    virtual bool equals(const Object* obj) const = 0;

    virtual std::size_t hash() const = 0;

    virtual std::string to_string() const = 0;
};

class Integer : public Number {
public:
    Integer(std::int64_t raw_int = 0);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    operator std::int64_t&();

private:
    std::int64_t raw_int;
};

class Float : public Number {
public:
    Float(double raw_float);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    operator double&();

private:
    double raw_float;
};

}

#endif
