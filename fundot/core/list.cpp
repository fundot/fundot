#include "list.h"

namespace fundot {

void List::trace() {
    Object::trace();
    for (auto& obj : raw_list) {
        obj->mark();
    }
}

bool List::equals(const Object* obj) const {
    auto other{dynamic_cast<const List*>(obj)};
    return other != nullptr && raw_list == other->raw_list;
}

std::string List::to_string() const {
    if (raw_list.empty()) {
        return "()";
    }
    std::string str{'('};
    for (auto& obj : raw_list) {
        str += obj->to_string();
        str += ", ";
    }
    str.pop_back();
    str.pop_back();
    str += ')';
    return str;
}

Object* List::eval() {
    if (raw_list.empty()) {
        return new Null;
    }
    auto iter{raw_list.cbegin()};
    auto end{--raw_list.cend()};
    while (iter != end) {
        (*iter)->eval();
        ++iter;
    }
    return (*end)->eval();
}

Object* List::quote(std::size_t count) {
    auto new_list{new List};
    for (const auto& obj : raw_list) {
        new_list->push_back(obj->quote(count));
    }
    return new_list;
}

std::size_t List::size() const {
    return raw_list.size();
}

void List::push_back(Object* obj) {
    raw_list.push_back(obj);
}

}