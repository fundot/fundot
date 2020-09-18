/**
 * @file object.h
 * 
 * @author Jiacheng Huang
 */

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

#include "identifier.h"

/**
 * A namespace for Fundot project.
 */
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

    /**
     * A class that stores and handles Fundot objects.
     */
    class Object
    {
    public:
        /**
         * Create a default Object that does not have value.
         */
        Object() = default;

        /**
         * Copy constructor: create an object that is a copy of another.
         * @param other Object to be copied.
         */
        Object(const Object &other) : _value(other._value) {}

        /**
         * Create an Object with a value of any type.
         * @tparam T Type of the value.
         * @param value Value to be copied.
         */
        template <typename T>
        Object(const T &value) : _value(value) {}

        /**
         * Assignment operator: set this object equal to another.
         * @param other Object to be copied.
         */
        Object &operator=(const Object &other) { _value = other._value; return *this; }

        /**
         * Bracket operator: access an Object with an index
         * if the value contained in this Object is of type std::vector<Object>.
         * @param index index of the Object to be accessed.
         */
        Object &operator[](size_t index);

        /**
         * Bracket operator: access an Object mapped by the key Identifier
         * if the value contained in this Object is of type std::map<Identifier, Object>.
         * @param id key of the Object to be accessed.
         */
        Object &operator[](const Identifier &id);

        /**
         * Get the reference of the value contained in this Object of a specific type.
         * @tparam T Type of the value.
         */
        template <typename T>
        T &value() { return *any_cast<T>(&_value); }

        /**
         * Get the type of the value contained in this Object.
         */
        const type_info &type() const { return _value.type(); }

        /**
         * Return true if the Object holds the given type.
         * @tparam T Type to check.
         */
        template <typename T>
        bool holds() const { return _value.type() == typeid(T); }

        /**
         * Extraction operator: extract the std::istream into an Object.
         * @param is std::istream to be extracted.
         * @param obj Object to store the extracted value.
         */
        friend istream &operator>>(istream &is, Object &obj);

        /**
         * Insertion operator: insert the object into the std::ostream.
         * @param os std::ostream to be inserted.
         * @param obj Object to insert.
         */
        friend ostream &operator<<(ostream &os, const Object &obj);

    private:
        any _value; /**< Data stored of any type. */
        set<char> _separators = {':', ',', '{', '}', '[', ']', '"', '(', ')'}; /**< Sepearatos in Fundot. */

        /**
         * Scan the std::istream and return an Object.
         * @param is std::istream to be scanned.
         */
        Object _scan(istream &is);

        /**
         * Scan the std::istream and return an Object that stores a value of type int or double.
         * @param is std::istream to be scanned.
         */
        Object _scanNumber(istream &is);
        
        /**
         * Scan the std::istream and return an Object that stores a value of type std::string.
         * @param is std::istream to be scanned.
         */
        Object _scanString(istream &is);

        /**
         * Scan the std::istream and return an Object that stores a value of type vector<Object>.
         * @param is std::istream to be scanned.
         */
        Object _scanVector(istream &is);

        /**
         * Scan the std::istream and return an Object that stores a value of type std::map<Identifier, Object>.
         * @param is std::istream to be scanned.
         */
        Object _scanMap(istream &is);

        /**
         * Scan the std::istream and return an Object that stores a value of type Identifier.
         * @param is std::istream to be scanned.
         */
        Object _scanIdentifier(istream &is);

        /**
         * Scan the std::istream and return an Object that stores a value of type std::list<Object>.
         * @param is std::istream to be scanned.
         */
        Object _scanList(istream &is);

        /** Print this Object to std::ostream.
         * @param os std::ostream to be printed.
         */
        void _print(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type int or double.
         * @param os std::ostream to be printed.
         */
        void _printNumber(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type std::string.
         * @param os std::ostream to be printed.
         */
        void _printString(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type vector<Object>.
         * @param os std::ostream to be printed.
         */
        void _printVector(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type std::map<Identifier, Object>.
         * @param os std::ostream to be printed.
         */
        void _printMap(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type Identifier.
         * @param os std::ostream to be printed.
         */
        void _printIdentifier(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type std::list<Object>.
         * @param os std::ostream to be printed.
         */
        void _printList(ostream &os) const;

        /** Print this Object to std::ostream if the value it contained is of type std::pair<Identifier, Object>.
         * @param os std::ostream to be printed.
         */
        void _printPair(ostream &os) const;
    };

} // namespace fundot

#endif