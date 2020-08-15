#include "scanner.h"

vector<string> Scanner::scan(istream &in)
{
    vector<string> expression;
    ios::sync_with_stdio(false);
    size_t start_count = 0, end_count = 0;
    while (start_count != end_count || start_count == 0)
    {
        string str;
        for (char c; in >> std::noskipws >> c;)
        {
            if (c == ' ' || c == '\t' || c == '\n')
            {
                break;
            }
            else if (c == '\'')
            {
                expression.push_back("Quote");
                vector<string> strv = scan(in);
                for (auto s : strv)
                {
                    expression.push_back(s);
                }
                expression.push_back(";");
            }
            else if (separators.find(string(1, c)) != separators.end())
            {
                if (isEnd(string(1, c)))
                {
                    ++end_count;
                }
                if (str.empty() == false)
                {
                    expression.push_back(str);
                    if (isStart(str))
                    {
                        ++start_count;
                    }
                    str.clear();
                }
                expression.push_back(string(1, c));
                break;
            }
            /*
            else if (c == ':')
            {
                if (str.empty() == false)
                {
                    expression.push_back(str);
                    str.clear();
                }
                expression.push_back(":");
                break;
            }
            */
            else if (c == '"')
            {
                str.push_back('"');
                while (in >> std::noskipws >> c && c != '"')
                {
                    str.push_back(c);
                }
                str.push_back('"');
            }
            else
            {
                str.push_back(c);
            }
        }
        if (isStart(str))
        {
            ++start_count;
        }
        else if (!str.empty() && start_count == 0)
        {
            expression.push_back(str);
            break;
        }
        if (str.empty() == false)
        {
            expression.push_back(str);
        }
    }
    ios::sync_with_stdio(true);
    return expression;
}