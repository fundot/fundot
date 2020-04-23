#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "expression.h"
#include "function.h"
#include "library.h"

std::map<std::string, Function> global_fun_map;
std::vector<std::map<std::string, Function>> local_fun_maps;

Expression::Expression(std::vector<std::string> strv)
{
    // !!!
    for (size_t i = 0; i < strv.size(); ++i)
    {
        strv_.push_back(strv[i]);
    }
}

Expression::Expression(std::string str)
{
    strv_.push_back(str);
}

bool Expression::isAtom()
{
    if (strv_.size() == 1 && isupper(strv_[0][0]) == 0)
    {
        return true;
    }
    else if (strv_.size() == 2)
    {
        if (strv_[0] == "List" && strv_[1] == ".")
        {
            return true;
        }
    }
    return false;
}

bool Expression::isFinal()
{
    if (isAtom())
    {
        return true;
    }
    else if (isupper(strv_[0][0]))
    {
        for (size_t i = 1; i < strv_.size(); ++i)
        {
            if (isupper(strv_[i][0]) && strv_[i] != "List")
            {
                return false;
            }
        }
    }
    return true;
}

Expression Expression::eval()
{
    // std::cout << strv_ << std::endl;
    if (strv_[0] == "Quote")
    {
        strv_.erase(strv_.begin());
        strv_.erase(strv_.end() - 1);
        return *this;
    }
    for (size_t i = 0; i < strv_.size(); ++i)
    {
        if (strv_[i] == "Quote")
        {
            i += getExpr(strv_, i).size();
            continue;
        }
        /*
        for (size_t j = 0; j < local_fun_maps.size(); ++j)
        {
            if (local_fun_maps[j].find(strv_[i]) != local_fun_maps[j].end())
            {
                std::vector<std::string> new_strv = local_fun_maps[j].at(strv_[i]).replaceFun(getExpr(strv_, i));
                strv_.erase(strv_.begin() + i, strv_.begin() + i + getExpr(strv_, i).size());
                strv_.insert(strv_.begin() + i, new_strv.begin(), new_strv.end());
            }
        }
        */
        if (global_fun_map.find(strv_[i]) != global_fun_map.end())
        {
            std::vector<std::string> new_strv = global_fun_map.at(strv_[i]).replaceFun(getExpr(strv_, i));
            strv_.erase(strv_.begin() + i, strv_.begin() + i + getExpr(strv_, i).size());
            strv_.insert(strv_.begin() + i, new_strv.begin(), new_strv.end());
        }
    }
    if (isFinal() == false)
    {
        for (size_t i = 0; i < strv_.size(); ++i)
        {
            if (isupper(strv_[i][0]) && i != 0)
            {
                Expression to_recurse(getExpr(strv_, i));
                strv_.erase(strv_.begin() + i, strv_.begin() + i + to_recurse.strv_.size());
                to_recurse = to_recurse.eval();
                strv_.insert(strv_.begin() + i, to_recurse.strv_.begin(), to_recurse.strv_.end());
                i += to_recurse.strv_.size() - 1;
            }
        }
    }
    if (strv_[0] == "Exit" || strv_[0] == "Quit")
    {
        exit(EXIT_SUCCESS);
    }
    else if (strv_[0] == "Def")
    {
        Function fun(*this);
        global_fun_map[fun.getName()] = fun;
        return Expression("null");
    }
    else if (strv_[0] == "Let")
    {
        Function fun(*this);
        local_fun_maps[local_fun_maps.size() - 1][fun.getName()] = fun;
        return Expression("null");
    }
    else if (strv_[0] == "Cond" || strv_[0] == "If")
    {
        size_t i = 1;
        while (i < strv_.size())
        {
            Expression predicate(getExpr(strv_, i));
            i += predicate.strv_.size();
            Expression expr(getExpr(strv_, i));
            if (predicate.eval().strv_[0] == "true" || predicate.eval().strv_[0] == "else")
            {
                return expr.eval();
            }
        }
    }
    else if (strv_[0] == "While")
    {
        size_t p = 1;
        Expression predicate(getExpr(strv_, 1));
        p += predicate.strv_.size();
        while (predicate.eval().strv_[0] == "true")
        {
            Expression expr(getExpr(strv_, p));
            expr.eval();
            predicate = Expression(getExpr(strv_, 1));
        }
        return Expression("null");
    }
    else if (strv_[0] == "Block")
    {
        // !!!
        std::map<std::string, Function> local_fun_map;
        local_fun_maps.push_back(local_fun_map);
        size_t last_start_index = 0;
        for (size_t i = 0; i < strv_.size(); ++i)
        {
            if (isupper(strv_[i][0]))
            {
                last_start_index = i;
            }
        }
        if (strv_[strv_.size() - 2] != ".")
        {
            last_start_index = strv_.size() - 2;
        }
        size_t i = 1;
        while (i < strv_.size() - 1)
        {
            Expression expr(getExpr(strv_, i));
            if (i == last_start_index)
            {
                local_fun_maps.erase(local_fun_maps.end() - 1);
                return expr;
            }
            ++i;
        }
        local_fun_maps.erase(local_fun_maps.end() - 1);
        return Expression("null");
    }
    else if (strv_[0] == "Call")
    {
        if (strv_[1][0] == '"')
        {
            strv_[1] = strv_[1].substr(1, strv_[1].size() - 2);
        }
        return Expression(readFile(strv_[1])).eval();
    }
    else if (strv_[0] == "List")
    {
        return *this;
    }
    else if (strv_[0] == "Eval")
    {
        return Expression(getExpr(strv_, 1)).eval();
    }
    else if (strv_[0] == "Atom")
    {
        // !!!
        if (Expression(getExpr(strv_, 1)).isAtom())
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Equal")
    {
        if (strv_[1] == strv_[2])
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "CAR" || strv_[0] == "First")
    {
        return Expression(getExpr(strv_, 2));
    }
    else if (strv_[0] == "CDR" || strv_[0] == "Rest")
    {
        std::vector<std::string> first = getExpr(strv_, 2);
        std::vector<std::string> rest = getExpr(strv_, 1);
        rest.erase(rest.begin() + 1, rest.begin() + 1 + first.size());
        return Expression(rest);
    }
    else if (strv_[0] == "Cons")
    {
        std::vector<std::string> element = getExpr(strv_, 1);
        std::vector<std::string> to_return = getExpr(strv_, 1 + element.size());
        if (isupper(to_return[0][0]) == 0)
        {
            to_return.insert(to_return.begin(), "List");
            to_return.push_back(".");
        }
        to_return.insert(to_return.begin() + 1, element.begin(), element.end());
        return Expression(to_return);
    }
    else if (strv_[0] == "File>>")
    {
        std::ifstream file_stream;
        file_stream.open(strv_[1]);
        std::string str;
        file_stream >> str;
        file_stream.close();
        return Expression(str);
    }
    else if (strv_[0] == "File<<")
    {
        std::ofstream file_stream;
        file_stream.open(strv_[1]);
        file_stream << strv_[2];
        file_stream.close();
        return Expression("null");
    }
    else if (strv_[0] == "Scan")
    {
        std::string str;
        std::cin >> str;
        return Expression(str);
    }
    else if (strv_[0] == "Print")
    {
        std::vector<std::string> new_strv(strv_.begin() + 1, strv_.end() - 1);
        if (new_strv[0][0] == '"')
        {
            new_strv[0] = new_strv[0].substr(1, new_strv[0].size() - 2);
        }
        std::cout << new_strv << std::endl;
        return Expression("null");
    }
    else if (strv_[0] == "Str@")
    {
        // !!!
        size_t i = std::stoull(strv_[2]);
        char c = strv_[1][i + 1];
        std::string str;
        str += c;
        return Expression(str);
    }
    else if (strv_[0] == "Num=")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first == second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Num<")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first < second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Num>")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first > second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Num<=")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first <= second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Num>=")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first >= second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Num+")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first + second));
    }
    else if (strv_[0] == "Num-")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first - second));
    }
    else if (strv_[0] == "Num*")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first * second));
    }
    else if (strv_[0] == "Num/")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first / second));
    }
    else if (strv_[0] == "Num%")
    {
        long long first = std::stoll(strv_[1]), second = std::stoll(strv_[2]);
        return Expression(numToStr(first % second));
    }
    else
    {
        return *this;
    }
    return Expression("null");
}

std::ostream &operator<<(std::ostream &out, Expression expr)
{
    for (size_t i = 0; i < expr.strv_.size(); ++i)
    {
        std::cout << expr.strv_[i] << " ";
    }
    return out;
}

std::vector<std::string> Expression::getStrv()
{
    return strv_;
}