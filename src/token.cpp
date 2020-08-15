#include "token.h"

const Token::Name &Token::name() const
{
    return token_name;
}

const string &Token::value() const
{
    return token_value;
}