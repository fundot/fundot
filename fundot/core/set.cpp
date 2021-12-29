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
    std::string str{'{'};
    for (auto& obj : raw_set) {
        str += obj->to_string();
        str += ", ";
    }
    str.pop_back();
    str.pop_back();
    str += '}';
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
    if (is_macro()) {
        auto args{dynamic_cast<Vector*>(obj)};
        if (args == nullptr) {
            throw Error{"argument is not a 'Vector'"};
        }
        return call_macro(args);
    }
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
    auto new_set{new Set};
    for (auto& obj : raw_set) {
        new_set->insert(obj->eval());
    }
    return new_set;
}

Object* Set::quote(std::size_t count) {
    auto new_set{new Set};
    for (const auto& obj : raw_set) {
        new_set->insert(obj->quote(count));
    }
    return new_set;
}

std::vector<Object*> Set::to_vector() const {
    return {raw_set.cbegin(), raw_set.cend()};
}

std::size_t Set::size() const {
    return raw_set.size();
}

void Set::insert(Object* obj) {
    raw_set.insert(obj);
}

bool Set::is_macro() {
    try {
        if (get(new Symbol{"__type__"})->equals(new Symbol{"__macro__"})) {
            return true;
        }
    } catch (Error& error) {
        return false;
    }
    return false;
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

Object* Set::call_macro(Vector* args) {
    auto params{dynamic_cast<Vector*>(get(new Symbol{"__params__"}))};
    auto body{get(new Symbol{"__body__"})};
    auto outer_context{get_local_context()};
    auto local_context{new Set};
    local_context->set(new Symbol{"__outer_context__"}, outer_context);
    for (std::size_t i{0}, size{params->size()}; i < size; ++i) {
        local_context->set(params->at(i), args->at(i));
    }
    set_local_context(local_context);
    auto obj{body->eval()};
    set_local_context(outer_context);
    return obj;
}

Object* Set::call_function(Vector* args) {
    auto params{dynamic_cast<Vector*>(get(new Symbol{"__params__"}))};
    auto body{get(new Symbol{"__body__"})};
    auto outer_context{get_local_context()};
    auto local_context{new Set};
    local_context->set(new Symbol{"__outer_context__"}, outer_context);
    for (std::size_t i{0}, size{params->size()}; i < size; ++i) {
        local_context->set(params->at(i), args->at(i)->eval());
    }
    set_local_context(local_context);
    auto obj{body->eval()};
    set_local_context(outer_context);
    return obj;
}

}
