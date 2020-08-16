#include "parser.h"

vector<Token> Parser::eval()
{
    /*
    for (vector<Token>::iterator iter = token_vector.begin(), last_iter = iter; iter != token_vector.end();)
    {
        cout << "token_vector:" << endl;
        for (auto tk : token_vector)
        {
            cout << tk.value() << " ";
        }
        cout << endl;
        if (iter->name() == Token::Name::OPERATOR)
        {
            cout << 1 << endl;
            static unordered_map<string, string> binary_operators{{"=", "Def"}, {"==", "Equal"}, {"+", "Add"}};
            cout << 2 << endl;
            if (binary_operators.find(iter->value()) != binary_operators.end())
            {
                cout << 3 << endl;
                iter = token_vector.erase(iter);
                cout << 4 << endl;
                token_vector.insert(last_iter, Token(Token::Name::KEYWORD, binary_operators[iter->value()]));
                cout << 5 << endl;
            }
        }
        cout << 1 << endl;
        last_iter = iter;
        cout << 2 << endl;
        getCompleteTokens(iter);
    }
    cout << "token_vector:" << endl;
    for (auto tk : token_vector)
    {
        cout << tk.value() << " ";
    }
    cout << endl;
    */
    vector<Token> to_return;
    if (token_vector[0].value() == "Quote")
    {
        to_return = vector<Token>(token_vector.begin() + 1, token_vector.end() - 1);
        return to_return;
    }
    vector<Token> tokens;
    tokens.push_back(*token_vector.begin());
    for (vector<Token>::iterator iter = token_vector.begin() + 1; iter != token_vector.end();)
    {
        if (iter->name() == Token::Name::KEYWORD || (iter->name() == Token::Name::IDENTIFIER && findObject(iter->value()).typeName() == "Function"))
        {
            vector<Token> tks = getCompleteTokens(iter);
            Parser parser(tks);
            for (auto tk : parser.eval())
            {
                tokens.push_back(tk);
            }
        }
        else
        {
            tokens.push_back(*iter++);
        }
    }
    if (tokens[0].name() == Token::Name::LITERAL)
    {
        to_return.push_back(tokens[0]);
    }
    else if (tokens[0].name() == Token::Name::IDENTIFIER)
    {
        Object object = findObject(tokens[0].value());
        if (object.typeName() == "Function")
        {
            Function fun = object.get<Function>();
            Parser parser(fun.replace(tokens));
            for (auto tk : parser.eval())
            {
                to_return.push_back(tk);
            }
        }
        else
        {
            to_return.push_back(Token(Token::Name::LITERAL, object.toString()));
        }
    }
    else if (tokens[0].value() == "Exit")
    {
        exit(0);
    }
    else if (tokens[0].value() == "Def")
    {
        Object object(tokens);
        object_scopes[object_scopes.size() - 1][tokens[1].value()] = object;
    }
    else if (tokens[0].value() == "Equal")
    {
        Object first(tokens[1]), second(tokens[2]);
        to_return.push_back(Token(Token::Name::LITERAL, (first == second).toString()));
    }
    else if (tokens[0].value() == "Add")
    {
        Object first(tokens[1]), second(tokens[2]);
        to_return.push_back(Token(Token::Name::LITERAL, (first + second).toString()));
    }
    else if (tokens[0].value() == "If")
    {
        for (vector<Token>::iterator iter = tokens.begin() + 1; iter != tokens.end();)
        {
            if (iter->value() == "true")
            {
                while ((++iter)->value() != "else" && isEnd(iter->value()) == false)
                {
                    to_return.push_back(*iter);
                }
                if ((++iter)->value() == "if")
                {
                    ++iter;
                }
            }
            else
            {
                while (iter->value() != "else" && isEnd(iter->value()) == false)
                {
                    ++iter;
                }
                if ((++iter)->value() == "if")
                {
                    ++iter;
                }
                else
                {
                    to_return.push_back(*iter);
                    break;
                }
            }
        }
    }
    return to_return;
}

vector<Token> Parser::getCompleteTokens(vector<Token>::iterator &iter)
{
    size_t start_count = 1, end_count = 0;
    vector<Token> tks;
    tks.push_back(*iter++);
    while (start_count != end_count)
    {
        if (isStart(iter->value()))
        {
            ++start_count;
        }
        else if (isEnd(iter->value()))
        {
            ++end_count;
        }
        tks.push_back(*iter++);
    }
    return tks;
}