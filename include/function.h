#ifndef __FUNCTION_H__
#define __FUNCTION_H__

class Function
{
public:
    Function() = default;
    Function(Expression expr);
    Function(std::vector<std::string> strv);
    std::string getName();
    std::vector<std::string> replaceFun(std::vector<std::string> strv);
private:
    std::string name_;
    std::vector<std::string> argv_;
    std::vector<std::string> body_;
};

#endif