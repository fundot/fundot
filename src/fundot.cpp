#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "expression.h"
#include "function.h"
#include "library.h"

int main(int argc, char **argv)
{
    std::cout << "Fun." << std::endl;
    if (argc == 2)
    {
        std::vector<std::string> strv = readFile(argv[1]);
        Expression expr(strv);
        Expression eval_expr = expr.eval();
        if (eval_expr.isNull() == false)
        {
            std::cout << eval_expr << std::endl;
        }
        return 0;
    }
    std::cout << ">>> ";
    std::vector<std::string> strv = readShell();
    while (strv[0] != "Exit")
    {
        Expression expr(strv);
        Expression eval_expr = expr.eval();
        if (eval_expr.isNull() == false)
        {
            std::cout << eval_expr << std::endl;
        }
        std::cout << ">>> ";
        strv = readShell();
    }
    return 0;
}