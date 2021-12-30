#include "fundot/repl/repl.h"
#include <fstream>

using namespace fundot;

int main(int argc, char* argv[]) {
    auto context{new Set};
    Object::set_global_context(context);
    Object::set_local_context(context);
    Object::add_root(context);
    context->set(new Symbol{"__outer_context__"}, new Null);
    auto parser{new Parser};
    context->set(new Symbol{"__parser__"}, parser);
    load_builtins(context);
    ReadEvalPrintLoop repl;
    if (argc == 1) {
        repl();
        return 0;
    }
    if (argc == 2) {
        std::string path{argv[1]};
        std::ifstream file{path};
        if (!file.is_open()) {
            throw Object::Error{"failed to open '" + path + '\''};
        }
        std::string expr{std::istreambuf_iterator<char>(file),
                         std::istreambuf_iterator<char>()};
        auto context{Object::get_local_context()};
        parser->parse(expr)->eval();
        return 0;
    }
    return 0;
}
