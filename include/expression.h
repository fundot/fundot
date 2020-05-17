#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

class Expression
{
public:
    friend class Function;
    friend std::ostream &operator<<(std::ostream &out, Expression expr);
    Expression(std::vector<std::string> strv);
    Expression(std::string str);
    Expression eval();
    bool isAtom();
    bool isFinal();
    bool isNull();

private:
    std::vector<std::string> strv_;
};

#endif