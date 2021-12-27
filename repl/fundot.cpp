#include "repl.h"

using namespace fundot;

int main() {
    auto scope{new Set};
    Object::set_scope(scope);
    Object::add_root(scope);
    scope->set(new Symbol{"__parent_scope__"}, new Null);
    auto parser{new Parser};
    scope->set(new Symbol{"__parser__"}, parser);
    load_builtins(scope);
    init_repl();
    repl();
    return 0;
}
