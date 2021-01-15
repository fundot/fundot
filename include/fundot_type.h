#ifndef FUNDOT_TYPE_H
#define FUNDOT_TYPE_H

#include <any>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

namespace fundot {

struct Object {
    std::any value;
};

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

struct Function {
    Vector params;
    Object body;
};

template<class T>
struct Hash;

template<>
struct Hash<Symbol> {
    std::size_t operator()(const Symbol& symbol) const
    {
        return std::hash<std::string>{}(symbol.value);
    }
};

template<>
struct Hash<String> {
    std::size_t operator()(const String& string) const
    {
        return std::hash<std::string>{}(string.value);
    }
};

template<>
struct Hash<Object> {
    std::size_t operator()(const Object& object) const
    {
        if (object.value.type() == typeid(String)) {
            return Hash<String>{}(std::any_cast<const String&>(object.value));
        }
        if (object.value.type() == typeid(Symbol)) {
            return Hash<Symbol>{}(std::any_cast<const Symbol&>(object.value));
        }
        if (object.value.type() == typeid(Setter)) {
            return Hash<Object>{}(
                std::any_cast<const Setter&>(object.value).value.first);
        }
        return 0;
    }
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

struct UnorderedSet {
    std::unordered_set<Object, Hash<Object>> value;
};

Object* get(Object& owner, const Object& index);

void set(Object& owner, const Object& index, const Object& value);

}  // namespace fundot

#endif
