#include "fundot.h"

int main()
{
    for (;;)
    {
        cout << ">>> ";
        Scanner scanner;
        Lexer lexer(scanner.scan(cin));
        Parser parser(lexer.lex());
        vector<Token> to_output(parser.eval());
        for (auto tk : to_output)
        {
            cout << tk.value() << " ";
        }
        if (to_output.empty() == false)
        {
            cout << endl;
        }
    }
    return 0;
}