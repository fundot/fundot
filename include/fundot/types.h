#ifndef FUNDOT_TYPE_H
#define FUNDOT_TYPE_H

#include <fstream>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

#include "object.h"

namespace fundot {

struct Boolean {
    bool value;
};

struct Integer {
    std::int64_t value;
};

struct Float {
    double value;
};

struct String {
    std::string value;
};

struct Symbol {
    std::string value;
};

struct Setter {
    std::pair<Object, Object> value;
};

struct Getter {
    std::pair<Object, Object> value;
};

struct Assignment {
    std::pair<Object, Object> value;
};

struct Adder {
    std::pair<Object, Object> value;
};

struct Subtractor {
    std::pair<Object, Object> value;
};

struct Multiplier {
    std::pair<Object, Object> value;
};

struct Divisor {
    std::pair<Object, Object> value;
};

struct Modular {
    std::pair<Object, Object> value;
};

struct Less {
    std::pair<Object, Object> value;
};

struct Greater {
    std::pair<Object, Object> value;
};

struct LessEqual {
    std::pair<Object, Object> value;
};

struct GreaterEqual {
    std::pair<Object, Object> value;
};

struct EqualTo {
    std::pair<Object, Object> value;
};

struct NotEqualTo {
    std::pair<Object, Object> value;
};

struct Negator {
    Object value;
};

struct And {
    std::pair<Object, Object> value;
};

struct Or {
    std::pair<Object, Object> value;
};

struct Not {
    Object value;
};

struct BitwiseAnd {
    std::pair<Object, Object> value;
};

struct BitwiseOr {
    std::pair<Object, Object> value;
};

struct BitwiseXor {
    std::pair<Object, Object> value;
};

struct LeftShift {
    std::pair<Object, Object> value;
};

struct RightShift {
    std::pair<Object, Object> value;
};

struct BitwiseNot {
    Object value;
};

struct Quote {
    Object value;
};

struct Null {
};

struct Void {
};

struct List {
    std::list<Object> value;
};

struct Vector {
    std::vector<Object> value;
};

struct UnorderedSet {
    std::unordered_set<Object, Hasher> value;
};

struct SpecialForm {
    std::function<Object(const List&)> value;
};

struct PrimitiveFunction {
    std::function<Object(const List&)> value;
};

struct SharedObject {
    std::shared_ptr<Object> value;
};

}  // namespace fundot

#endif
