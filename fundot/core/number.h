#ifndef FUNDOT_CORE_NUMBER_H
#define FUNDOT_CORE_NUMBER_H

#include "object.h"
#include <cstdint>

namespace fundot {

class Number : public Object {
public:
    virtual int int_value() const;

    virtual double double_value() const;
};

class Integer : public Number {
public:
    Integer(std::int64_t raw_int = 0);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    int int_value() const override;

    double double_value() const override;

private:
    std::int64_t raw_int;
};

class Float : public Number {
public:
    Float(double raw_float = 0);

    bool equals(const Object* obj) const override;

    std::size_t hash() const override;

    std::string to_string() const override;

    int int_value() const override;

    double double_value() const override;

private:
    double raw_float;
};

}

#endif
