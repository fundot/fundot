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
        else if (c == '(')
        {
            return _scanList(is);
        }
        else if (_separators.find(c) != _separators.end())
        {
            return Object(c);
        }
        else
        {
            is.putback(c);
            return _scanIdentifier(is);
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
        map<Identifier, Object> obj_map;
        Object obj(_scan(is));
        char c;
        while ((obj.getType() == typeid(char) && obj.getValue<char>() == '}') == false)
        {
            is >> c;
            if (c != ':')
            {
                // error handle
            }
            obj_map[obj.getValue<Identifier>()] = _scan(is);
            is >> c;
            if (c == '}')
            {
                break;
            }
            obj = _scan(is);
        }
        return Object(obj_map);
    }

    Object Object::_scanIdentifier(istream &is)
    {
        Identifier id;
        char c;
        is >> noskipws;
        while (is >> c)
        {
            if (_separators.find(c) != _separators.end())
            {
                is.putback(c);
                break;
            }
            else if (isspace(c))
            {
                break;
            }
            id.push_back(c);
        }
        is >>skipws;
        return Object(id);
    }

    Object Object::_scanList(istream &is)
    {
        list<Object> obj_lst;
        Object obj(_scan(is));
        while ((obj.getType() == typeid(char) && obj.getValue<char>() == ')') == false)
        {
            obj_lst.push_back(obj);
            obj = _scan(is);
        }
        return Object(obj_lst);
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
        else if (_value.type() == typeid(map<Identifier, Object>))
        {
            _printMap(os);
        }
        else if (_value.type() == typeid(Identifier))
        {
            _printIdentifier(os);
        }
        else if (_value.type() == typeid(list<Object>))
        {
            _printList(os);
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
        while (it != obj_vct.end())
        {
            os << *it++;
            if (it != obj_vct.end())
            {
                os << ", ";
            }
        }
        os << ']';
    }

    void Object::_printMap(ostream &os) const
    {
        os << '{';
        map<Identifier, Object> obj_map = any_cast<map<Identifier, Object>>(_value);
        map<Identifier, Object>::iterator it = obj_map.begin();
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

    void Object::_printIdentifier(ostream &os) const
    {
        os << any_cast<Identifier>(_value);
    }

    void Object::_printList(ostream &os) const
    {
        os << '(';
        list<Object> obj_lst = any_cast<list<Object>>(_value);
        list<Object>::iterator it = obj_lst.begin();
        while (it != obj_lst.end())
        {
            
            os << *it++;
            if (it != obj_lst.end())
            {
                os << ' ';
            }
        }
        os << ')';
    }

} // namespace fundot

int main()
{
    fundot::Object obj;
    cin >> obj;
    cout << obj << '\n';
    return 0;
}