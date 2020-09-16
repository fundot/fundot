#ifndef OBJECT_H
#define OBJECT_H

#include <any>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

namespace fundot
{
    using std::any;
    using std::any_cast;
    using std::istream;
    using std::list;
    using std::map;
    using std::noskipws;
    using std::ostream;
    using std::pair;
    using std::set;
    using std::skipws;
    using std::string;
    using std::type_info;
    using std::vector;

    struct Identifier : public string
    {
        Identifier() = default;
        Identifier(const string &str) : string(str) {}
    };

    class Object
    {
    public:
        Object() = default;

        Object(const Object &other) : _value(other._value) {}

        template <typename T>
        Object(const T &value) : _value(value) {}

        void operator=(const Object &other) { _value = other._value; }

        Object &operator[](size_t index);
        Object &operator[](Identifier id);

        template <typename T>
        T &value() { return *any_cast<T>(&_value); }

        const type_info &type() const { return _value.type(); }

        friend istream &operator>>(istream &is, Object &obj);
        friend ostream &operator<<(ostream &os, const Object &obj);

    private:
        any _value;
        set<char> _separators = {':', ',', '{', '}', '[', ']', '"', '(', ')'};
        Object _scan(istream &is);
        Object _scanNumber(istream &is);
        Object _scanString(istream &is);
        Object _scanVector(istream &is);
        Object _scanMap(istream &is);
        Object _scanIdentifier(istream &is);
        Object _scanList(istream &is);
        void _print(ostream &os) const;
        void _printNumber(ostream &os) const;
        void _printString(ostream &os) const;
        void _printVector(ostream &os) const;
        void _printMap(ostream &os) const;
        void _printIdentifier(ostream &os) const;
        void _printList(ostream &os) const;
    };

} // namespace fundot

#endif