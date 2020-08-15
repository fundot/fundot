#ifndef __PARSER_H__
#define __PARSER_H__

#include <cstdlib>
#include <string>
#include <vector>
#include "object.h"
#include "token.h"

using namespace std;

class Parser
{
public:
    Parser(const vector<Token> &init_token_vector) : token_vector(init_token_vector) {}

    vector<Token> eval();
    
    vector<Token> getCompleteTokens(vector<Token>::iterator &iter);

private:
    vector<Token> token_vector;
};

#endif