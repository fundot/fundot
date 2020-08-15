#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <vector>
#include <unordered_set>
#include "global.h"
#include "token.h"

using namespace std;

class Lexer
{
public:
    Lexer(const vector<string> &init_expression) : expression(init_expression) {}
    vector<Token> lex();

private:
    vector<string> expression;
};

#endif