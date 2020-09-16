#include "../include/fundot.h"

namespace fundot
{
    Object Fundot::eval(Object &obj)
    {
        if (obj.type() == typeid(list<Object>))
        {
            list<Object> &obj_lst = obj.value<list<Object>>();
            if (obj_lst.front().type() == typeid(Identifier))
            {
                map<Identifier, Object> &obj_map = _obj.value<map<Identifier, Object>>();
                if (obj_map.find(obj_lst.front().value<Identifier>()) != obj_map.end())
                {
                    return _obj;
                }
            }
        }
        return Object();
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
        static const map<Identifier, Object> function_definitions = {{static_cast<Identifier>("type"), static_cast<Identifier>("function")}};
        static vector<string> functions = {"quote", "add"};
        for (size_t i = 0; i < functions.size(); ++i)
        {
            _obj.value<map<Identifier, Object>>()[functions[i]] = Object(function_definitions);
        }
    }

    Object Fundot::_add(const Object &obj)
    {
        return "Hello";
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