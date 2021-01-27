#include <boost/dll.hpp>
#include <fstream>
#include <iostream>

#include "fundot/fundot.h"

using namespace fundot;

int main(int argc, char* argv[])
{
    Evaluator eval;
    boost::dll::fs::path path =
        boost::dll::program_location().parent_path().parent_path();
    if (std::filesystem::exists((path / "init.fun").string())) {
        eval("(import \"" + (path / "init.fun").string() + "\")");
    }
    if (argc == 1) {
        Object to_eval;
        Object after_eval;
        Reader read;
        Printer print;
        while (std::cin) {
            try {
                std::cout << ">>> ";
                read(to_eval, std::cin);
                if (!std::cin) {
                    std::cout << std::endl;
                    return 0;
                }
                after_eval = eval(to_eval);
                print(after_eval, std::cout);
                std::cout << '\n';
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
            }
        }
        std::cout << std::endl;
        return 0;
    }
    if (argc == 2) {
        try {
            std::ifstream file(argv[1]);
            Object to_eval;
            Reader read;
            while (file) {
                read(to_eval, file);
                eval(to_eval);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
        return 0;
    }
    return 0;
}
