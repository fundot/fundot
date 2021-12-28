#include "fundot/repl/repl.h"
using namespace fundot;

int main() {
    auto context{new Set};
    Object::set_global_context(context);
    Object::set_local_context(context);
    Object::add_root(context);
    context->set(new Symbol{"__outer_context__"}, new Null);
    auto parser{new Parser};
    context->set(new Symbol{"__parser__"}, parser);
    load_builtins(context);
    init_repl();
    repl();
    return 0;
}
