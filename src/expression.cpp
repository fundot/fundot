#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "expression.h"
#include "function.h"
#include "library.h"

extern std::map<std::string, Function> global_fun_map;

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
    else if (strv_[0] == "Set")
    {
        std::vector<std::string> new_strv = getExpr(strv_, 2);
        Expression expr(new_strv);
        new_strv = expr.eval().strv_;
        new_strv.insert(new_strv.begin(), strv_[1]);
        new_strv.insert(new_strv.begin(), "Set");
        new_strv.push_back(".");
        Function fun(new_strv);
        global_fun_map[fun.getName()] = fun;
        return Expression("null");
    }
    else if (strv_[0] == "Quote")
    {
        strv_[0] = "List";
        return *this;
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
                return expr.eval();
            }
            i += expr.strv_.size();
            expr.eval();
        }
        return Expression("null");
    }
    for (size_t i = 0; i < strv_.size(); ++i)
    {
        if (global_fun_map.find(strv_[i]) != global_fun_map.end())
        {
            std::vector<std::string> new_strv = global_fun_map.at(strv_[i]).replaceFun(getExpr(strv_, i));
            strv_.erase(strv_.begin() + i, strv_.begin() + i + getExpr(strv_, i).size());
            strv_.insert(strv_.begin() + i, new_strv.begin(), new_strv.end());
        }
    }
    while (isFinal() == false)
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
    if (strv_[0] == "Call")
    {
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
    else if (strv_[0] == "Print")
    {
        std::vector<std::string> new_strv(strv_.begin() + 1, strv_.end() - 1);
        std::cout << new_strv << std::endl;
        return Expression("null");
    }
    else if (strv_[0] == "Less")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first < second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Greater")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        if (first > second)
        {
            return Expression("true");
        }
        return Expression("false");
    }
    else if (strv_[0] == "Add")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first + second));
    }
    else if (strv_[0] == "Sub")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first - second));
    }
    else if (strv_[0] == "Mul")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first * second));
    }
    else if (strv_[0] == "Div")
    {
        double first = std::stod(strv_[1]), second = std::stod(strv_[2]);
        return Expression(numToStr(first / second));
    }
    else if (strv_[0] == "Mod")
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