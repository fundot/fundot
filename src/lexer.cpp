#include "lexer.h"

vector<Token> Lexer::lex()
{
    vector<Token> tokens;
    for (size_t i = 0; i < expression.size(); ++i)
    {
        if (keywords.find(expression[i]) != keywords.end())
        {
            Token token(Token::Name::KEYWORD, expression[i]);
            tokens.push_back(token);
        }
        else if (separators.find(expression[i]) != separators.end())
        {
            Token token(Token::Name::SEPARATOR, expression[i]);
            tokens.push_back(token);
        }
        else if (isIdentifier(expression[i]))
        {
            Token token(Token::Name::IDENTIFIER, expression[i]);
            tokens.push_back(token);
        }
        else if (operators.find(expression[i]) != operators.end())
        {
            Token token(Token::Name::OPERATOR, expression[i]);
            tokens.push_back(token);
        }
        else
        {
            Token token(Token::Name::LITERAL, expression[i]);
            tokens.push_back(token);
        }
    }
    return tokens;
}