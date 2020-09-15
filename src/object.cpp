#include "../include/object.h"

#include "../include/debug.h"

namespace fundot
{
    istream &operator>>(istream &is, Object &obj)
    {
        obj = obj._scan(is);
        return is;
    }

    ostream &operator<<(ostream &os, const Object &obj)
    {
        obj._print(os);
        return os;
    }

    Object Object::_scan(istream &is)
    {
        char c;
        is >> c;
        if (c == '"')
        {
            return _scanString(is);
        }
        else if (c == '[')
        {
            return _scanVector(is);
        }
        else if (c == '{')
        {
            return _scanMap(is);
        }
        return Object(c);
    }

    Object Object::_scanString(istream &is)
    {
        is >> noskipws;
        string str;
        char c;
        while (is >> c)
        {
            if (c == '"')
            {
                break;
            }
            str.push_back(c);
        }
        Object obj(str);
        is >> skipws;
        return obj;
    }

    Object Object::_scanVector(istream &is)
    {
        vector<Object> obj_vct;
        Object obj(_scan(is));
        char c;
        while ((obj.getType() == typeid(char) && obj.getValue<char>() == ']') == false)
        {
            obj_vct.push_back(obj);
            is >> c;
            if (c == ']')
            {
                break;
            }
            obj = _scan(is);
        }
        return Object(obj_vct);
    }

    Object Object::_scanMap(istream &is)
    {
        map<string, Object> obj_map;
        Object obj(_scan(is));
        char c;
        while ((obj.getType() == typeid(char) && obj.getValue<char>() == ']') == false)
        {
            is >> c;
            if (c != ':')
            {
                // error handle
            }
            obj_map[obj.getValue<string>()] = _scan(is);
            is >> c;
            if (c == '}')
            {
                break;
            }
            obj = _scan(is);
        }
        return Object(obj_map);
    }

    void Object::_print(ostream &os) const
    {
        if (_value.type() == typeid(string))
        {
            _printString(os);
        }
        else if (_value.type() == typeid(vector<Object>))
        {
            _printVector(os);
        }
        else if (_value.type() == typeid(map<string, Object>))
        {
            _printMap(os);
        }
    }

    void Object::_printString(ostream &os) const
    {
        os << '"' << any_cast<string>(_value) << '"';
    }

    void Object::_printVector(ostream &os) const
    {
        os << '[';
        vector<Object> obj_vct = any_cast<vector<Object>>(_value);
        vector<Object>::iterator it = obj_vct.begin();
        while (it != obj_vct.end() - 1)
        {
            os << *it++ << ", ";
        }
        os << *it << ']';
    }

    void Object::_printMap(ostream &os) const
    {
        os << '{';
        map<string, Object> obj_map = any_cast<map<string, Object>>(_value);
        map<string, Object>::iterator it = obj_map.begin();
        while (it != obj_map.end())
        {
            os << it->first << ": " << it->second;
            ++it;
            if (it != obj_map.end())
            {
                os << ", ";
            }
        }
        os << '}';
    }

} // namespace fundot

// test

#include <iostream>

using namespace fundot;

int main()
{
    Object obj;
    cin >> obj;
    cout << obj << endl;
    return 0;
}