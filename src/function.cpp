#include "function.h"

Function::Function(const vector<Token> &init_tokens)
{
    cout << "init_tokens: ";
    for (auto tk : init_tokens)
    {
        cout << tk.value() << " ";
    }
    cout << endl;
    size_t i = 2;
    while (init_tokens[i].value() != ":")
    {
        argv.push_back(init_tokens[i++]);
    }
    ++i;
    while (i < init_tokens.size() - 1)
    {
        body.push_back(init_tokens[i++]);
    }
    cout << "argv: ";
    for (auto tk : argv)
    {
        cout << tk.value() << " ";
    }
    cout << endl;
    cout << "body: ";
    for (auto tk : body)
    {
        cout << tk.value() << " ";
    }
    cout << endl;
}

vector<Token> Function::replace(const vector<Token> &tokens) const
{
    unordered_map<string, Token> arg_map;
    for (size_t i = 1; i < tokens.size(); ++i)
    {
        arg_map[argv[i - 1].value()] = tokens[i];
    }
    vector<Token> to_return;
    for (size_t i = 0; i < body.size(); ++i)
    {
        if (arg_map.find(body[i].value()) != arg_map.end())
        {
            to_return.push_back(arg_map[body[i].value()]);
        }
        else
        {
            to_return.push_back(body[i]);
        }
    }
    return to_return;
}