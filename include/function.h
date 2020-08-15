#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include <unordered_set>
#include <vector>
#include "global.h"
#include "token.h"

using namespace std;

class Function
{
public:
    Function(const vector<Token> &init_tokens);

    vector<Token> replace(const vector<Token> &tokens) const;


    vector<Token> argv;
    vector<Token> body;
};

#endif