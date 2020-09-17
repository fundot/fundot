#include "../include/fundot.h"

namespace fundot
{
    Object Fundot::eval(Object &obj)
    {
        if (obj.type() == typeid(list<Object>))
        {
            list<Object> &obj_lst = obj.value<list<Object>>();
            if (obj_lst.empty())
            {
                return obj;
            }
            if (obj_lst.front().type() == typeid(Identifier))
            {
                Identifier id = obj_lst.front().value<Identifier>();
                map<Identifier, Object> &obj_map = _obj.value<map<Identifier, Object>>();
                if (obj_map.find(obj_lst.front().value<Identifier>()) != obj_map.end())
                {
                    if (obj_map[id].type() == typeid(map<Identifier, Object>))
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
                    }
                }
            }
            else
            {
                return obj_lst.front();
            }
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
        static const map<Identifier, Object> fun_defs = {{static_cast<Identifier>("type"), static_cast<Identifier>("built-in-function")}};
        static vector<string> fun_ids = {"quote", "add", "exit"};
        for (size_t i = 0; i < fun_ids.size(); ++i)
        {
            _obj[fun_ids[i]] = Object(fun_defs);
        }
    }

    Object Fundot::_add(Object &obj)
    {
        double sum = 0;
        list<Object> obj_lst = obj.value<list<Object>>();
        for (list<Object>::iterator it = ++obj_lst.begin(); it != obj_lst.end(); ++it)
        {
            if (it->type() == typeid(int))
            {
                sum += it->value<int>();
            }
            else if (it->type() == typeid(double))
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

using namespace fundot;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        Fundot fdt;
        fdt.repl(std::cin, std::cout);
    }
    else if (argc == 2)
    {
    }
    return 0;
}