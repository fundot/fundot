#include "parser.h"

vector<Token> Parser::eval()
{
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
    if (tokens[0].name() == Token::Name::IDENTIFIER)
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
    if (tokens[0].value() == "Exit")
    {
        exit(0);
    }
    else if (tokens[0].value() == "Def")
    {
        Object object(tokens);
        object_scopes[object_scopes.size() - 1][tokens[1].value()] = object;
    }
    else if (tokens[0].value() == "Num+")
    {
        double first = stod(tokens[1].value()), second = stod(tokens[2].value());
        double sum = first + second;
        to_return.push_back(Token(Token::Name::LITERAL, to_string(sum)));
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