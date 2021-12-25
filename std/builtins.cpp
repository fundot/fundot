#include "builtins.h"

namespace fundot {

void load_builtins(Object* obj) {
    obj->set(new Symbol{"cond"}, new SpecialForm{builtin_cond});
}

}
