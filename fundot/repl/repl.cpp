#include "repl.h"

namespace fundot {

Object* repl_read_line(Vector* args) {
    if (args->size() > 1) {
        throw Object::Error{"'read_line' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    std::string prompt;
    if (args->size() == 1) {
        auto obj{args->at(0)};
        auto str{dynamic_cast<String*>(obj)};
        if (str != nullptr) {
            prompt = str->string_value();
        } else {
            prompt = obj->to_string();
        }
    }
    auto scope{Object::get_scope()};
    auto reader{dynamic_cast<Reader*>(scope->get(new Symbol{"__reader__"}))};
    if (reader == nullptr) {
        throw Object::Error{"'__reader__' is not a 'Reader'"};
    }
    return new String{reader->read_line(prompt)};
}

void init_repl() {
    auto scope{Object::get_scope()};
    auto reader{new Reader};
    scope->set(new Symbol{"__reader__"}, reader);
    scope->set(new Symbol{"read_line"}, new PrimitiveFunction{repl_read_line});
}

int repl() {
    auto scope{Object::get_scope()};
    auto parser{dynamic_cast<Parser*>(scope->get(new Symbol{"__parser__"}))};
    if (parser == nullptr) {
        throw Object::Error{"'__parser__' is not a 'Parser'"};
    }
    auto reader{dynamic_cast<Reader*>(scope->get(new Symbol{"__reader__"}))};
    if (reader == nullptr) {
        throw Object::Error{"'__reader__' is not a 'Reader'"};
    }
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
}

}
