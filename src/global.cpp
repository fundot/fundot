#include "global.h"

vector<unordered_map<string, Object>> object_scopes(1);
unordered_set<string> keywords{ "Exit", "Quote", "Def", "Num+" };
unordered_set<string> separators{ ";", ":" };

Object null_object;

bool isIdentifier(string to_find)
{
    for (ptrdiff_t i = object_scopes.size() - 1; i >= 0; --i)
    {
        if (object_scopes[i].find(to_find) != object_scopes[i].end())
        {
            return true;
        }
    }
    return false;
}

bool isStart(string str)
{
    if (keywords.find(str) != keywords.end())
    {
        return true;
    }
    for (ptrdiff_t i = object_scopes.size() - 1; i >= 0; --i)
    {
        if (object_scopes[i].find(str) != object_scopes[i].end() && object_scopes[i][str].typeName() == "Function")
        {
            return true;
        }
    }
    return false;
}

bool isEnd(string str)
{
    return str == ";";
}

Object &findObject(string identifier)
{
    for (ptrdiff_t i = object_scopes.size() - 1; i >= 0; --i)
    {
        if (object_scopes[i].find(identifier) != object_scopes[i].end())
        {
            return object_scopes[i][identifier];
        }
    }
    return null_object;
}