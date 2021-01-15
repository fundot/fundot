#ifndef FUNDOT_IO_H
#define FUNDOT_IO_H

#include <iostream>

#include "fundot_type.h"

namespace fundot {

std::istream& operator>>(std::istream& is, List& list);

std::istream& operator>>(std::istream& is, Vector& vector);

std::istream& operator>>(std::istream& is, UnorderedSet& set);

std::istream& operator>>(std::istream& is, Object& object);

std::ostream& operator<<(std::ostream& os, const List& list);

std::ostream& operator<<(std::ostream& os, const Vector& vector);

std::ostream& operator<<(std::ostream& os, const UnorderedSet& set);

std::ostream& operator<<(std::ostream& os, const Object& object);

struct Scanner {
    std::istream& operator()(std::istream& is, Object& object) const;
};

}  // namespace fundot

#endif
