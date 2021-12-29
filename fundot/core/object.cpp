#include "object.h"

namespace fundot {

Object::Color Object::roots;

Object::Color Object::white;

Object::Color Object::gray;

Object::Color Object::black;

Object* Object::global_context{nullptr};

Object* Object::local_context{nullptr};

bool Object::Equal::operator()(const Object* lhs, const Object* rhs) const {
    return lhs->equals(rhs) || rhs->equals(lhs);
}

std::size_t Object::Hash::operator()(const Object* obj) const {
    return obj->hash();
}

Object::Object() {
    white.push_front(this);
    color = &white;
    iter = color->begin();
}

Object::~Object() {
    color->erase(iter);
}

void Object::trace() {
    if (color != &black) {
        black.splice(black.cbegin(), *color, iter);
        color = &black;
    }
}

bool Object::equals(const Object* obj) const {
    return this == obj;
}

std::size_t Object::hash() const {
    std::string message{'\''};
    message += typeid(*this).name();
    message += '\'';
    message += " is not hashable";
    throw Error{message};
}

std::string Object::to_string() const {
    std::string str{'<'};
    str += typeid(*this).name();
    str += '>';
    return str;
}

Object* Object::get(Object* obj) const {
    std::string message{'\''};
    message += typeid(*this).name();
    message += '\'';
    message += " is not gettable";
    throw Error{message};
}

Object* Object::set(Object* index, Object* value) {
    std::string message{'\''};
    message += typeid(*this).name();
    message += '\'';
    message += " is not gettable";
    throw Error{message};
}

Object* Object::call(Object* obj) {
    std::string message{'\''};
    message += typeid(*this).name();
    message += '\'';
    message += " is not callable";
    throw Error{message};
}

Object* Object::eval() {
    return this;
}

Object* Object::quote(std::size_t count) {
    return this;
}

void Object::mark() {
    if (color == &white) {
        gray.splice(gray.cbegin(), *color, iter);
        color = &gray;
    }
}

void Object::add_root(Object* obj) {
    roots.push_front(obj);
}

void Object::collect() {
    for (auto& root : roots) {
        root->mark();
    }
    while (!gray.empty()) {
        gray.front()->trace();
    }
    while (!white.empty()) {
        delete white.front();
    }
    while (!black.empty()) {
        auto obj{black.front()};
        white.splice(white.cbegin(), *obj->color, obj->iter);
        obj->color = &white;
    }
}

Object* Object::get_global_context() {
    return global_context;
}

Object* Object::get_local_context() {
    return local_context;
}

void Object::set_global_context(Object* context) {
    Object::global_context = context;
}

void Object::set_local_context(Object* context) {
    Object::local_context = context;
}

}
