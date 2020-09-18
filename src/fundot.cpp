#include "../include/fundot.h"

namespace fundot
{
    Fundot::Fundot() : _obj(map<Identifier, Object>())
    {
        _local_scope = &_obj.value<map<Identifier, Object>>();
        _init();
    }

    Object Fundot::eval(Object &obj)
    {
        if (obj.holds<list<Object>>())
        {
            return _evalList(obj);
        }
        else if (obj.holds<Identifier>())
        {
            return _evalIdentifier(obj);
        }
        else if (obj.holds<pair<Identifier, Object>>())
        {
            return _evalPair(obj);
        }
        else if (obj.holds<vector<Object>>())
        {
            return _evalVector(obj);
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

    Object Fundot::_evalList(Object &obj)
    {
        list<Object> &obj_lst = obj.value<list<Object>>();
        if (obj_lst.front().holds<Identifier>())
        {
            Identifier &id = obj_lst.front().value<Identifier>();
            if (_local_scope->count(id) > 0)
            {
                if (id == "quote")
                {
                    return *(++obj_lst.begin());
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
                else if (id == "show")
                {
                    return _obj;
                }
            }
        }
        return obj;
    }

    Object Fundot::_evalIdentifier(Object &obj)
    {
        Identifier &id = obj.value<Identifier>();
        size_t dot_pos = id.str().find('.');
        map<Identifier, Object> *map_ptr = _local_scope;
        Identifier id_copy = id;
        while (dot_pos != string::npos)
        {
            if (map_ptr->count(id_copy.str().substr(0, dot_pos)) > 0)
            {
                if ((*map_ptr)[id_copy.str().substr(0, dot_pos)].holds<map<Identifier, Object>>())
                {
                    map_ptr = &(*map_ptr)[id_copy.str().substr(0, dot_pos)].value<map<Identifier, Object>>();
                    id_copy = id_copy.str().substr(dot_pos + 1, id_copy.str().length() - dot_pos - 1);
                    dot_pos = id_copy.str().find('.');
                    if (dot_pos == string::npos)
                    {
                        return (*map_ptr)[id_copy];
                    }
                }
                else
                {
                    return (*map_ptr)[id_copy.str().substr(0, dot_pos)];
                }
            }
        }
        if (_local_scope->count(id) > 0)
        {
            return eval((*_local_scope)[id]);
        }
        return obj;
    }

    Object Fundot::_evalPair(Object &obj)
    {
        pair<Identifier, Object> &obj_pair = obj.value<pair<Identifier, Object>>();
        obj_pair.second = eval(obj_pair.second);
        _obj[obj_pair.first] = obj_pair.second;
        return obj;
    }

    Object Fundot::_evalVector(Object &obj)
    {
        vector<Object> &obj_vct = obj.value<vector<Object>>();
        for (size_t i = 0; i < obj_vct.size(); ++i)
        {
            obj_vct[i] = eval(obj_vct[i]);
        }
        return obj_vct;
    }

    void Fundot::_init()
    {
        static const map<Identifier, Object> fun_defs = {{Identifier("type"), Identifier("built-in-function")}};
        static const vector<string> fun_ids = {"quote", "add", "exit", "show"};
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