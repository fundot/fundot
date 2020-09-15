#ifndef OBJECT_H
#define OBJECT_H

#include <any>
#include <iostream>
#include <typeinfo>
#include <map>
#include <vector>

using std::istream;
using std::noskipws;
using std::string;
using std::map;
using namespace std; // Don't forget to delete this.

namespace fundot
{
    class Object
    {
    public:
        Object() = default;

        template <typename T>
        Object(T value) : _value(value) {}

        template <typename T>
        T getValue() const { return any_cast<T>(_value); }

        const type_info &getType() const { return _value.type(); }

        bool operator<(const Object &other);

        friend istream &operator>>(istream &is, Object &obj);
        friend ostream &operator<<(ostream &os, const Object &obj);

    private:
        any _value;
        Object _scan(istream &is);
        Object _scanString(istream &is);
        Object _scanVector(istream &is);
        Object _scanMap(istream &is);
        void _print(ostream &os) const;
        void _printString(ostream &os) const;
        void _printVector(ostream &os) const;
        void _printMap(ostream &os) const;
    };

} // namespace fundot

#endif