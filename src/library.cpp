#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "library.h"

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

std::vector<std::string> readFile(std::string file_name)
{
    std::ifstream file_stream;
    file_stream.open(file_name);
    std::vector<std::string> strv;
    while (isFullExpr(strv) == false)
    {
        // std::cout << strv << std::endl;
        // !!!
        std::string str;
        file_stream >> str;
        strv.push_back(str);
        size_t p = strv.size() - 1;
        for (size_t i = strv[p].length() - 1; i > 0 && strv[p][i] == '.'; --i)
        {
            strv[p] = strv[p].substr(0, strv[p].length() - 1);
            strv.push_back(".");
        }
    }
    file_stream.close();
    return strv;
}

std::vector<std::string> readShell()
{
    std::vector<std::string> strv;
    while (isFullExpr(strv) == false)
    {
        // !!!
        std::string str;
        std::cin >> str;
        strv.push_back(str);
        size_t p = strv.size() - 1;
        for (size_t i = strv[p].length() - 1; i > 0 && strv[p][i] == '.'; --i)
        {
            strv[p] = strv[p].substr(0, strv[p].length() - 1);
            strv.push_back(".");
        }
    }
    return strv;
}

std::string numToStr(double num)
{
    if (num - static_cast<int>(num) < EPSILON)
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