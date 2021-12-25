#include "builtins.h"

namespace fundot {

void load_builtins(Object* obj) {
    obj->set(new Symbol{"cond"}, new SpecialForm{builtin_cond});
    obj->set(new Symbol{"while"}, new SpecialForm{builtin_while});
}

}
