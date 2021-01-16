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
        std::ifstream file(argv[1]);
        if (file.is_open()) {
            Scanner scan;
            Object to_eval;
            Evaluator eval;
            while (file) {
                scan(file, to_eval);
                eval(to_eval);
            }
        }
        return 0;
    }
    return 0;
}
