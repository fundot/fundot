#ifndef OBJECT_H
#define OBJECT_H

#include <any>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <typeinfo>
#include <vector>

using std::any;
using std::cin;
using std::cout;
using std::istream;
using std::list;
using std::map;
using std::noskipws;
using std::ostream;
using std::set;
using std::skipws;
using std::string;
using std::type_info;
using std::vector;

using namespace std;

namespace fundot
{
    struct Identifier : public string
    {
    };

    class Object
    {
    public:
        Object() = default;

        template <typename T>
        Object(T value) : _value(value) {}

        template <typename T>
        T getValue() const { return any_cast<T>(_value); }

        const type_info &getType() const { return _value.type(); }

        friend istream &operator>>(istream &is, Object &obj);
        friend ostream &operator<<(ostream &os, const Object &obj);

    private:
        any _value;
        set<char> _separators = {':', ',', '{', '}', '[', ']', '"', '(', ')'};
        Object _scan(istream &is);
        Object _scanString(istream &is);
        Object _scanVector(istream &is);
        Object _scanMap(istream &is);
        Object _scanIdentifier(istream &is);
        Object _scanList(istream &is);
        void _print(ostream &os) const;
        void _printString(ostream &os) const;
        void _printVector(ostream &os) const;
        void _printMap(ostream &os) const;
        void _printIdentifier(ostream &os) const;
        void _printList(ostream &os) const;
    };

} // namespace fundot

#endif