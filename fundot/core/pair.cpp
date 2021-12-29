#include "pair.h"

namespace fundot {

Pair::Pair(Object* first, Object* second) : raw_pair{first, second} {
}

void Pair::trace() {
    Object::trace();
    raw_pair.first->mark();
    raw_pair.second->mark();
}

bool Pair::equals(const Object* obj) const {
    auto other{dynamic_cast<const Pair*>(obj)};
    return other != nullptr && raw_pair == other->raw_pair;
}

Object* Pair::get(Object* obj) const {
    auto index{dynamic_cast<Integer*>(obj)};
    if (index == nullptr) {
        throw Error{"index '" + obj->to_string()
                    + "' not available in a 'Pair'"};
    }
    switch (index->int_value()) {
    case 0:
        return raw_pair.first;
    case 1:
        return raw_pair.second;
    default:
        throw Error{"index '" + index->to_string() + "' out of range"};
    }
}

Object* Pair::set(Object* index, Object* value) {
    auto pos{dynamic_cast<Integer*>(index)};
    if (index == nullptr) {
        throw Error{"index '" + index->to_string()
                    + "' not available in a 'Pair'"};
    }
    switch (pos->int_value()) {
    case 0:
        raw_pair.first = value;
        break;
    case 1:
        raw_pair.second = value;
        break;
    default:
        throw Error{"index '" + index->to_string() + "' out of range"};
    }
    return value;
}

Object*& Pair::first() {
    return raw_pair.first;
}

Object* const& Pair::first() const {
    return raw_pair.first;
}

Object*& Pair::second() {
    return raw_pair.second;
}

Object* const& Pair::second() const {
    return raw_pair.second;
}

Getter::Getter(Object* first, Object* second) : Pair{first, second} {
}

std::string Getter::to_string() const {
    return first()->to_string() + "." + second()->to_string();
}

Object* Getter::eval() {
    return first()->eval()->get(second()->eval());
}

Object* Getter::quote(std::size_t count) {
    return new Getter{first()->quote(count), second()->quote(count)};
}

Setter::Setter(Object* first, Object* second) : Pair{first, second} {
}

bool Setter::equals(const Object* obj) const {
    auto other{dynamic_cast<const Setter*>(obj)};
    if (other != nullptr) {
        return first()->equals(other->first());
    }
    return first()->equals(obj);
}

std::size_t Setter::hash() const {
    return first()->hash();
}

std::string Setter::to_string() const {
    return first()->to_string() + ": " + second()->to_string();
}

Object* Setter::eval() {
    auto getter{dynamic_cast<Getter*>(first())};
    if (getter != nullptr) {
        return getter->first()->eval()->set(getter->second(), second()->eval());
    }
    return get_global_context()->set(first(), second()->eval());
}

Object* Setter::quote(std::size_t count) {
    return new Setter{first()->quote(count), second()->quote(count)};
}

}
