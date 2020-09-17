#include "../include/fundot.h"

namespace fundot
{
    Object Fundot::eval(Object &obj)
    {
        map<Identifier, Object> &obj_map = _obj.value<map<Identifier, Object>>();
        if (obj.holds<list<Object>>())
        {
            list<Object> &obj_lst = obj.value<list<Object>>();
            if (obj_lst.front().holds<Identifier>())
            {
                Identifier &id = obj_lst.front().value<Identifier>();
                if (obj_map.count(id) > 0)
                {
                    if (id == "quote")
                    {
                        return ++obj_lst.begin();
                    }
                    for (list<Object>::iterator it = ++obj_lst.begin(); it != obj_lst.end(); ++it)
                    {
                        *it = eval(*it);
                    }
                    if (id == "add")
                    {
                        return _add(obj);
                    }
                    else if (id == "exit")
                    {
                        exit(0);
                    }
                }
            }
        }
        else
        {
            return obj;
        }

        return obj;
    }

    void Fundot::repl(istream &is, ostream &os)
    {
        Object obj;
        for (size_t i = 0;; ++i)
        {
            os << "Fundot> ";
            is >> obj;
            os << eval(obj) << endl;
        }
    }

    void Fundot::_init()
    {
        static const map<Identifier, Object> fun_defs = {{Identifier("type"), Identifier("built-in-function")}};
        static const vector<string> fun_ids = {"quote", "add", "exit"};
        for (size_t i = 0; i < fun_ids.size(); ++i)
        {
            _obj[fun_ids[i]] = fun_defs;
        }
    }

    Object Fundot::_add(Object &obj)
    {
        double sum = 0;
        list<Object> &obj_lst = obj.value<list<Object>>();
        for (list<Object>::iterator it = ++obj_lst.begin(); it != obj_lst.end(); ++it)
        {
            if (it->holds<int>())
            {
                sum += it->value<int>();
            }
            else if (it->holds<double>())
            {
                sum += it->value<double>();
            }
            else
            {
                // error handling
            }
        }
        return Object(sum);
    }
} // namespace fundot