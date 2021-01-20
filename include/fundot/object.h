#ifndef FUNDOT_OBJECT_H
#define FUNDOT_OBJECT_H

#include <any>
#include <memory>

namespace fundot {

struct Object {
    std::any value;
};

struct Hasher {
    std::size_t operator()(const Object& object) const;
};

class Reader {
public:
    std::istream& operator()(Object& object, std::istream& is) const;

    Reader();

    ~Reader();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

class Evaluator {
public:
    Object operator()(const Object& object);

    Evaluator();

    ~Evaluator();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

class Printer {
public:
    std::ostream& operator()(const Object& object, std::ostream& os) const;

    Printer();

    ~Printer();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

bool operator<(const Object& lhs, const Object& rhs);

bool operator>(const Object& lhs, const Object& rhs);

bool operator<=(const Object& lhs, const Object& rhs);

bool operator>=(const Object& lhs, const Object& rhs);

bool operator==(const Object& lhs, const Object& rhs);

bool operator!=(const Object& lhs, const Object& rhs);

Object operator+(const Object& lhs, const Object& rhs);

Object operator-(const Object& lhs, const Object& rhs);

Object operator*(const Object& lhs, const Object& rhs);

Object operator/(const Object& lhs, const Object& rhs);

Object operator%(const Object& lhs, const Object& rhs);

Object operator-(const Object& object);

Object operator&&(const Object& lhs, const Object& rhs);

Object operator||(const Object& lhs, const Object& rhs);

Object operator!(const Object& object);

Object operator&(const Object& lhs, const Object& rhs);

Object operator|(const Object& lhs, const Object& rhs);

Object operator^(const Object& lhs, const Object& rhs);

Object operator~(const Object& object);

Object operator<<(const Object& lhs, const Object& rhs);

Object operator>>(const Object& lhs, const Object& rhs);

std::istream& operator>>(std::istream& is, Object& object);

std::ostream& operator<<(std::ostream& os, const Object& object);

}  // namespace fundot

#endif
