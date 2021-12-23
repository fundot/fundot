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
    switch (*index) {
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
    switch (*pos) {
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

Getter::Getter(Object* first, Object* second) : Pair{first, second} {
}

std::string Getter::to_string() const {
    return get(new Integer{0})->to_string() + "."
           + get(new Integer{1})->to_string();
}

Object* Getter::eval() {
    return get(new Integer{0})->eval()->get(get(new Integer{1}));
}

Setter::Setter(Object* first, Object* second) : Pair{first, second} {
}

bool Setter::equals(const Object* obj) const {
    auto other{dynamic_cast<const Setter*>(obj)};
    if (other != nullptr) {
        return get(new Integer{0})->equals(other->get(new Integer{0}));
    }
    return get(new Integer{0})->equals(obj);
}

std::size_t Setter::hash() const {
    return get(new Integer{0})->hash();
}

std::string Setter::to_string() const {
    return get(new Integer{0})->to_string() + ": "
           + get(new Integer{1})->to_string();
}

Object* Setter::eval() {
    auto getter{dynamic_cast<Getter*>(get(new Integer{0}))};
    if (getter != nullptr) {
        return getter->get(new Integer{0})
            ->eval()
            ->set(getter->get(new Integer{1}), get(new Integer{1})->eval());
    }
    return get_scope()->set(get(new Integer{0}), get(new Integer{1})->eval());
}

}
