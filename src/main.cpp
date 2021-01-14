#include <fstream>

#include "fundot_eval.h"

using namespace fundot;

int main(int argc, char* argv[])
{
    if (argc == 1) {
        Scanner scan;
        Object to_eval;
        Evaluator eval;
        Object after_eval;
        std::cout << ">>> ";
        while (scan(std::cin, to_eval)) {
            after_eval = eval(to_eval);
            if (after_eval.value.type() != typeid(Void)) {
                std::cout << after_eval << '\n';
            }
            std::cout << ">>> ";
        }
        std::cout << std::endl;
        return 0;
    }
    if (argc == 2) {
        std::fstream file(argv[1], std::ios_base::in | std::ios_base::app);
        if (file.is_open()) {
            file.seekg(-1, std::ios_base::end);
            char last_char;
            file >> last_char;
            if (std::isspace(last_char) == false) {
                file << "\n";
            }
            file.clear();
            file.seekg(0);
            Scanner scan;
            Evaluator eval;
            for (Object to_eval; scan(file, to_eval); eval(to_eval)) {}
        }
        return 0;
    }
    return 0;
}