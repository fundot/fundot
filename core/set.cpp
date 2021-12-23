#include "set.h"

namespace fundot {

void Set::trace() {
    Object::trace();
    for (auto& obj : raw_set) {
        obj->mark();
    }
}

bool Set::equals(const Object* obj) const {
    auto other{dynamic_cast<const Set*>(obj)};
    return other != nullptr && raw_set == other->raw_set;
}

std::string Set::to_string() const {
    if (raw_set.empty()) {
        return "{}";
    }
    std::string str{"{"};
    for (auto& obj : raw_set) {
        str += obj->to_string();
        str += ", ";
    }
    str.pop_back();
    str.pop_back();
    str += "}";
    return str;
}

Object* Set::get(Object* obj) const {
    auto found{raw_set.find(obj)};
    if (found == raw_set.end()) {
        throw Error{"key '" + obj->to_string() + "' not found"};
    }
    auto setter{dynamic_cast<Setter*>(*found)};
    if (setter == nullptr) {
        throw Error{"no value bound to '" + (*found)->to_string() + "'"};
    }
    return setter->second();
}

Object* Set::set(Object* index, Object* value) {
    raw_set.erase(index);
    raw_set.insert(new Setter{index, value});
    return value;
}

Object* Set::call(Object* obj) {
    if (is_function()) {
        auto args{dynamic_cast<Vector*>(obj)};
        if (args == nullptr) {
            throw Error{"argument is not a 'Vector'"};
        }
        return call_function(args);
    }
    throw Error{"not a callable 'Set'"};
}

Object* Set::eval() {
    for (auto& obj : raw_set) {
        auto setter{dynamic_cast<Setter*>(obj)};
        if (setter != nullptr) {
            setter->second()->eval();
        }
    }
    return this;
}

void Set::insert(Object* obj) {
    raw_set.insert(obj);
}

bool Set::is_function() {
    try {
        if (get(new Symbol{"__type__"})->equals(new Symbol{"__fn__"})) {
            return true;
        }
    } catch (Error& error) {
        return false;
    }
    return false;
}

Object* Set::call_function(Vector* args) {
    auto params{dynamic_cast<Vector*>(get(new Symbol{"__params__"}))};
    auto body{get(new Symbol{"__body__"})};
    auto parent_scope{get_scope()};
    auto current_scope{new Set};
    current_scope->set(new Symbol{"__previous_scope__"}, parent_scope);
    parent_scope->set(new Symbol{"__next_scope__"}, current_scope);
    for (std::size_t i{0}, size{params->size()}; i < size; ++i) {
        current_scope->set(params->at(i), args->at(i)->eval());
    }
    set_scope(current_scope);
    auto obj{body->eval()};
    set_scope(parent_scope);
    parent_scope->set(new Symbol{"__next_scope__"}, new Null);
    return obj;
}

}
