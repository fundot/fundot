#ifndef FUNDOT_H
#define FUNDOT_H

#include "object.h"

namespace fundot
{
    using std::endl;

    class Fundot
    {
    public:
        Fundot() : _obj(map<Identifier, Object>()) { _init(); }

        Object eval(Object &obj);

        void repl(istream &is, ostream &os);

        friend ostream &operator<<(ostream &os, const Fundot &fdt);

    private:
        Object _obj;
        void _init();
        Object _add(Object &obj);
    };

    ostream &operator<<(ostream &os, const Fundot &fdt)
    {
        os << fdt._obj;
        return os;
    }
} // namespace fundot

#endif