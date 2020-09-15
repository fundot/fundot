#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

namespace fundot
{
    class Scanner
    {
    public:
        string &scanString(istream &is);

    private:
        unordered_set<string> _separators = {";"};
    };
} // namespace fundot

#endif