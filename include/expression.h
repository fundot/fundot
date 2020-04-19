#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

class Expression
{
public:
    friend std::ostream &operator<<(std::ostream &out, Expression expr);
    Expression(std::vector<std::string> strv);
    Expression(std::string str);
    Expression eval();
    std::vector<std::string> getStrv();
    bool isAtom();
    bool isFinal();
    void replaceFun();

private:
    std::vector<std::string> strv_;
};

#endif