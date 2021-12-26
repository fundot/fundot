#include "builtins.h"

namespace fundot {

void load_builtins(Object* obj) {
    obj->set(new Symbol{"cond"}, new SpecialForm{builtin_cond});
    obj->set(new Symbol{"while"}, new SpecialForm{builtin_while});
    auto parser{dynamic_cast<Parser*>(
        Object::get_scope()->get(new Symbol{"__parser__"}))};
    register_addition_operator(parser);
    register_subtraction_operator(parser);
}

}
