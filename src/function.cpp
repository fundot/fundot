#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "expression.h"
#include "function.h"
#include "library.h"

extern std::map<std::string, Function> global_fun_map;

Function::Function(Expression expr)
{
    // !!!
    name_ = expr.getStrv()[1];
    size_t p = 1;
    argv_ = getExpr(expr.getStrv(), p);
    p += argv_.size();
    body_ = getExpr(expr.getStrv(), p);
}

Function::Function(std::vector<std::string> strv)
{
    // !!!
    name_ = strv[1];
    size_t p = 1;
    argv_ = getExpr(strv, p);
    p += argv_.size();
    body_ = getExpr(strv, p);
}

std::string Function::getName()
{
    return name_;
}

std::vector<std::string> Function::replaceFun(std::vector<std::string> strv)
{
    std::vector<std::string> to_return;
    std::map<std::string, Function> local_fun_map;
    int p = 1;
    for (size_t i = 1; i < argv_.size() - 1; ++i)
    {
        std::vector<std::string> new_strv = getExpr(strv, p);
        p += new_strv.size();
        new_strv.insert(new_strv.begin(), argv_[i]);
        new_strv.insert(new_strv.begin(), "Def");
        new_strv.push_back(".");
        Function fun(new_strv);
        std::pair<std::string, Function> to_insert(fun.name_, fun);
        local_fun_map.insert(to_insert);
    }
    for (size_t i = 0; i < body_.size(); ++i)
    {
        if (local_fun_map.find(body_[i]) != local_fun_map.end())
        {
            to_return.insert(to_return.end(), local_fun_map.at(body_[i]).body_.begin(), local_fun_map.at(body_[i]).body_.end());
        }
        else
        {
            to_return.push_back(body_[i]);
        }
    }
    Expression expr(to_return);
    to_return = expr.eval().getStrv();
    return to_return;
}