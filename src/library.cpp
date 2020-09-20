#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "library.h"

std::map<char, std::string> symbol_map = {{'{', "Block"}, {'[', "Vect"}, {'\'', "'"}};

bool isFunStart(std::string str)
{
    if (isupper(str[0]))
    {
        return true;
    }
    return false;
}

bool isFunEnd(std::string str)
{
    if (str == ".")
    {
        return true;
    }
    return false;
}

bool isFullExpr(std::vector<std::string> strv)
{
    if (strv.empty())
    {
        return false;
    }
    size_t start_count = 0, end_count = 0;
    for (size_t i = 0; i < strv.size(); ++i)
    {
        if (isFunStart(strv[i]))
        {
            ++start_count;
        }
        else if (isFunEnd(strv[i]))
        {
            ++end_count;
        }
    }
    if (start_count == end_count)
    {
        return true;
    }
    // !!!
    return false;
}

bool isFullExpr(std::vector<std::string> strv, size_t p, size_t q)
{
    if (strv.empty())
    {
        return false;
    }
    size_t start_count = 0, end_count = 0;
    for (size_t i = p; i < q + 1; ++i)
    {
        if (isFunStart(strv[i]))
        {
            ++start_count;
        }
        else if (isFunEnd(strv[i]))
        {
            ++end_count;
        }
    }
    if (start_count == end_count)
    {
        return true;
    }
    // !!!
    return false;
}

std::vector<std::string> getExpr(std::vector<std::string> strv, size_t p)
{
    std::vector<std::string> new_strv;
    for (size_t i = p; i < STRV_MAX; ++i)
    {
        // !!!
        new_strv.push_back(strv[i]);
        if (isFullExpr(new_strv))
        {
            break;
        }
    }
    return new_strv;
}

bool isStartSymbol(char c)
{
    if (symbol_map.find(c) != symbol_map.end())
    {
        return true;
    }
    return false;
}

bool isEndSymbol(char c)
{
    if (c == '.' || c == '}' || c == ']')
    {
        return true;
    }
    return false;
}

void symbolSplit(std::vector<std::string> &strv, size_t p)
{
    while (isStartSymbol(strv[p][0]))
    {
        if (strv[p].length() == 1)
        {
            strv[p] = symbol_map[strv[p][0]];
            break;
        }
        strv.push_back(strv[p].substr(1, strv[p].length() - 1));
        strv[p] = symbol_map[strv[p][0]];
        ++p;
    }
    if (isEndSymbol(strv[p][0]))
    {
        strv[p][0] = '.';
    }
    for (size_t i = strv[p].length() - 1; i > 0 && isEndSymbol(strv[p][i]); --i)
    {
        strv[p] = strv[p].substr(0, strv[p].length() - 1);
        strv.push_back(".");
    }
}

std::vector<std::string> readStream(std::istream &in)
{
    std::vector<std::string> strv;
    while (isFullExpr(strv) == false)
    {
        // !!!
        std::string str;
        in >> str;
        strv.push_back(str);
        size_t p = strv.size() - 1;
        if (strv[p][0] == '"' && strv[p].find_last_of('"') == 0)
        {
            char c = in.get();
            while (c != '"')
            {
                if (c == '\\')
                {
                    c = in.get();
                }
                strv[p] += c;
                c = in.get();
            }
            strv[p] += c;
            c = in.get();
            while (c != ' ' && c != '\t' && c != '\n')
            {
                strv[p] += c;
                c = in.get();
            }
        }
        symbolSplit(strv, p);
    }
    for (size_t i = 0; i < strv.size(); ++i)
    {
        if (strv[i] == "'")
        {
            strv[i] = "Quote";
            size_t p = i + getExpr(strv, i + 1).size() + 1;
            strv.insert(strv.begin() + p, ".");
        }
        else if (strv[i][strv[i].size() - 1] == '\'')
        {
            strv[i].erase(strv[i].end() - 1);
            size_t p = i + getExpr(strv, i).size() - 1;
            strv.insert(strv.begin() + p, ".");
            strv.insert(strv.begin() + i + 1, "Quote");
        }
    }
    return strv;
}

std::vector<std::string> readFile(std::string file_name)
{
    std::ifstream file_stream;
    file_stream.open(file_name);
    std::vector<std::string> strv;
    strv = readStream(file_stream);
    file_stream.close();
    return strv;
}

std::vector<std::string> readShell()
{
    return readStream(std::cin);
}

std::string numToStr(double num)
{
    if (num - static_cast<long long>(num) < EPSILON)
    {
        return std::to_string(static_cast<long long>(num));
    }
    return std::to_string(num);
}

std::ostream &operator<<(std::ostream &out, std::vector<std::string> strv)
{
    for (size_t i = 0; i < strv.size(); ++i)
    {
        std::cout << strv[i] << " ";
    }
    return out;
}