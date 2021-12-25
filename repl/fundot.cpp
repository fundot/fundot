#include "reader.h"
#include "std/builtins.h"
#include <iostream>

using namespace fundot;

int main() {
    auto scope{new Set};
    Object::set_scope(scope);
    Object::add_root(scope);
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
            std::cout << parser->parse(input)->eval()->to_string() << '\n';
        } catch (Object::Error& error) {
            std::cerr << "Exception: " << error.what() << '\n';
        }
        Object::collect();
    }
    return 0;
}
