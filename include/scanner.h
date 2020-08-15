#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <iostream>
#include <string>
#include <vector>
#include "global.h"

using namespace std;

class Scanner
{
public:
    Scanner() = default;
    vector<string> scan(istream &in);
};

#endif