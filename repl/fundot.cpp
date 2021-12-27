#include "reader.h"
#include "std/builtins.h"
#include <iostream>

using namespace fundot;

int main() {
    auto scope{new Set};
    Object::set_scope(scope);
    Object::add_root(scope);
    scope->set(new Symbol{"__parent_scope__"}, new Null);
    auto parser{new Parser};
    scope->set(new Symbol{"__parser__"}, parser);
    auto reader{new Reader};
    scope->set(new Symbol{"__reader__"}, reader);
    load_builtins(scope);
    for (;;) {
        try {
            std::string input{reader->read()};
            if (input.empty()) {
                continue;
            }
            auto evaluated{parser->parse(input)->eval()};
            if (evaluated->equals(new Null)) {
                continue;
            }
            std::cout << evaluated->to_string() << '\n';
        } catch (const std::exception& error) {
            std::cerr << "Exception: " << error.what() << '\n';
        }
        Object::collect();
    }
    return 0;
}
