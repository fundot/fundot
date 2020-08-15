#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>

using namespace std;

class Token
{
public:
    enum Name
    {
        IDENTIFIER,
        KEYWORD,
        SEPARATOR,
        OPERATOR,
        LITERAL,
        COMMENT
    };

    Token() = default;
    Token(const Name &init_name, const string &init_value) : token_name(init_name), token_value(init_value) {}

    const Name &name() const;
    const string &value() const;

private:
    Name token_name;
    string token_value;
};

#endif