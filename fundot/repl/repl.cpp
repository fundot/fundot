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
    auto context{Object::get_local_context()};
    auto reader{dynamic_cast<Reader*>(context->get(new Symbol{"__reader__"}))};
    if (reader == nullptr) {
        throw Object::Error{"'__reader__' is not a 'Reader'"};
    }
    return new String{reader->read_line(prompt)};
}

void init_repl() {
    auto context{Object::get_local_context()};
    auto reader{new Reader};
    context->set(new Symbol{"__reader__"}, reader);
    context->set(new Symbol{"read_line"},
                 new PrimitiveFunction{repl_read_line});
}

int repl() {
    auto context{Object::get_local_context()};
    auto parser{dynamic_cast<Parser*>(context->get(new Symbol{"__parser__"}))};
    if (parser == nullptr) {
        throw Object::Error{"'__parser__' is not a 'Parser'"};
    }
    auto reader{dynamic_cast<Reader*>(context->get(new Symbol{"__reader__"}))};
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
