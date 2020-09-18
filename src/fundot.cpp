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
                else if ((*_local_scope)[id].holds<map<Identifier, Object>>())
                {
                    map<Identifier, Object> *last_local = _local_scope;
                    _local_scope = &(*_local_scope)[id].value<map<Identifier, Object>>();
                    Object to_return;
                    if (_local_scope->count(Identifier("type")) > 0 && (*_local_scope)[Identifier("type")].holds<Identifier>())
                    {
                        if ((*_local_scope)[Identifier("type")].value<Identifier>() == "function")
                        {
                            if ((_local_scope->count(Identifier("params")) > 0 && (*_local_scope)[Identifier("params")].holds<vector<Object>>()))
                            {
                                to_return = _evalFunction(obj);
                            }
                        }
                    }
                    _local_scope = last_local;
                    return to_return;
                }
            }
        }
        return obj;
    }

    Object Fundot::_evalIdentifier(Object &obj)
    {
        Identifier &id = obj.value<Identifier>();
        size_t dot_pos = id.str().find('.');
        map<Identifier, Object> *previous_scope = _local_scope;
        Object to_return;
        if (dot_pos != string::npos)
        {
            if (_local_scope->count(id.str().substr(0, dot_pos)) > 0)
            {
                if ((*_local_scope)[id.str().substr(0, dot_pos)].holds<map<Identifier, Object>>())
                {
                    Object to_eval = Identifier(id.str().substr(dot_pos + 1, id.str().length() - dot_pos - 1));
                    _local_scope = &(*_local_scope)[id.str().substr(0, dot_pos)].value<map<Identifier, Object>>();
                    to_return = _evalIdentifier(to_eval);
                    _local_scope = previous_scope;
                    return to_return;
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
        Identifier &id = obj_pair.first;
        size_t dot_pos = id.str().find('.');
        map<Identifier, Object> *previous_scope = _local_scope;
        while (dot_pos != string::npos)
        {
            if (_local_scope->count(id.str().substr(0, dot_pos)) > 0)
            {
                if ((*_local_scope)[id.str().substr(0, dot_pos)].holds<map<Identifier, Object>>())
                {
                    _local_scope = &(*_local_scope)[id.str().substr(0, dot_pos)].value<map<Identifier, Object>>();
                    id = id.str().substr(dot_pos + 1, id.str().length() - dot_pos - 1);
                    dot_pos = id.str().find('.');
                    if (dot_pos == string::npos)
                    {
                        break;
                    }
                }
            }
        }
        (*_local_scope)[obj_pair.first] = obj_pair.second;
        _local_scope = previous_scope;
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

    Object Fundot::_evalFunction(Object &obj)
    {
        list<Object> &obj_lst = obj.value<list<Object>>();
        for (list<Object>::iterator it = obj_lst.begin(); it != obj_lst.end(); ++it)
        {
        }
        return obj;
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