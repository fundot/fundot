#include "vector.h"

namespace fundot {

void Vector::trace() {
    Object::trace();
    for (auto& obj : raw_vec) {
        obj->mark();
    }
}

bool Vector::equals(const Object* obj) const {
    auto other{dynamic_cast<const Vector*>(obj)};
    return other != nullptr && raw_vec == other->raw_vec;
}

std::string Vector::to_string() const {
    if (raw_vec.empty()) {
        return "[]";
    }
    std::string str{"["};
    for (auto& obj : raw_vec) {
        str += obj->to_string();
        str += ", ";
    }
    str.pop_back();
    str.pop_back();
    str += "]";
    return str;
}

Object* Vector::get(Object* obj) const {
    auto pos{dynamic_cast<Integer*>(obj)};
    if (pos == nullptr) {
        throw Error{"index '" + pos->to_string() + "' is not an 'Integer'"};
    }
    return raw_vec.at(pos->int_value());
}

Object* Vector::set(Object* index, Object* value) {
    auto pos{dynamic_cast<Integer*>(index)};
    if (index == nullptr) {
        throw Error{"index '" + pos->to_string() + "' is not an 'Integer'"};
    }
    return raw_vec.at(pos->int_value()) = value;
}

Object* Vector::eval() {
    if (raw_vec.empty()) {
        throw Error{"empty 'Vector'"};
    }
    auto args{new Vector};
    std::size_t i{1};
    std::size_t end{raw_vec.size()};
    while (i < end) {
        args->push_back(raw_vec[i]);
        ++i;
    }
    return raw_vec[0]->eval()->call(args);
}

Object*& Vector::at(std::size_t pos) {
    return raw_vec.at(pos);
}

bool Vector::empty() const {
    return raw_vec.empty();
}

std::size_t Vector::size() const {
    return raw_vec.size();
}

std::size_t Vector::erase(std::size_t pos) {
    raw_vec.erase(raw_vec.begin() + pos);
    return pos;
}

void Vector::push_back(Object* obj) {
    raw_vec.push_back(obj);
}

}
