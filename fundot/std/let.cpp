#include "builtins.h"

namespace fundot {

Object* builtin_let(Vector* args) {
    if (args->size() < 1) {
        throw Object::Error{
            "'let' takes at least 1 argument but none was given"};
    }
    auto bindings{dynamic_cast<Vector*>(args->at(0))};
    if (bindings == nullptr) {
        throw Object::Error{"first argument of 'let' is not a 'Vector'"};
    }
    auto outer_context{Object::get_local_context()};
    auto local_context{new Set};
    for (std::size_t i{0}, size{bindings->size()}; i < size; ++i) {
        auto binding{dynamic_cast<Setter*>(bindings->at(i))};
        if (binding == nullptr) {
            throw Object::Error{
                "one of the binding expressions of 'let' is not a 'Setter'"};
        }
        local_context->set(binding->first(), binding->second()->eval());
    }
    local_context->set(new Symbol{"__outer_context__"}, outer_context);
    Object::set_local_context(local_context);
    if (args->size() == 1) {
        return new Null;
    }
    for (std::size_t i{1}, size{args->size() - 1}; i < size; ++i) {
        args->at(i)->eval();
    }
    auto result{args->at(args->size() - 1)->eval()};
    Object::set_local_context(outer_context);
    return result;
}

}
