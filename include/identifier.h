/**
 * @file identifier.h
 * 
 * @author Jiacheng Huang
 */

#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

namespace fundot
{
    using std::string;

    /**
     * A class that has a std::string member.
     * This class is used to help C++ differentiate identifier from string, 
     * because identifier and string are two different types of objects in Fundot.
     */
    class Identifier
    {
    public:
        /**
         * Create an empty Identifier.
         */
        Identifier() = default;

        /**
         * Create an Identifier with a std::string.
         * @param str std::string to be copied.
         */
        Identifier(const string &str) : _str(str) {}

        /**
         * Return a reference to the std::string in this Identifier.
         */
        string &str() { return _str; }

        /**
         * Equality operator: compare a std::string with the member std::string.
         * Return true if the std::string in this Identifier euqals the one given.
         * @param str std::string to compare with.
         */
        bool operator==(const string &str) const { return _str == str; }

        /**
         * Equality operator: compare std::string in an Identifier with that in this Identifier.
         * Return true if the std::string in this Identifier euqals the one in the given Identifier.
         * @param other Identifier to compare with.
         */
        bool operator==(const Identifier &other) const { return _str == other._str; }

        /**
         * Less than operator: compare std::string in an Identifier with that in this Identifier.
         * Return true if the std::string in this Identifier is less than the one in the given Identifier.
         * @param other Identifier to compare with.
         */
        bool operator<(const Identifier &other) const { return _str < other._str; }

    private:
        string _str; /**< String data of Identifer. */
    };
} // namespace fundot

#endif