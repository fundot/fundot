#include <fstream>
#include "../include/fundot.h"

using std::ifstream;

using namespace fundot;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        Fundot fdt;
        fdt.repl();
    }
    else if (argc == 2)
    {
        string file_name(argv[1]);
        if (file_name.substr(file_name.length() - 3, 3) == ".fd")
        {
            ifstream fs;
            fs.open(argv[1]);
            Object obj;
            fs >> obj;
            Fundot fdt(fs);
            fdt.eval(obj);
            fs.close();
        }
    }
    return 0;
}