#include "../include/fundot.h"

using namespace fundot;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        Fundot fdt;
        fdt.repl(std::cin, std::cout);
    }
    else if (argc == 2)
    {
    }
    return 0;
}