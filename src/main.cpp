#include <fstream>
#include <iostream>

#include "object.h"

using namespace fundot;

int main(int argc, char* argv[])
{
    if (argc == 1) {
        Object object;
        Reader read;
        Evaluator eval;
        Printer print;
        std::cout << ">>> ";
        while (read(object, std::cin)) {
            print(eval(object), std::cout);
            std::cout << "\n>>> ";
        }
        std::cout << std::endl;
        return 0;
    }
    if (argc == 2) {
        std::ifstream file(argv[1]);
        if (file.is_open()) {
            Object to_eval;
            Reader read;
            Evaluator eval;
            while (file) {
                read(to_eval, file);
                eval(to_eval);
            }
        }
        return 0;
    }
    return 0;
}
