/**
 * MIT License

 * Copyright (c) 2020 Jiacheng Huang

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "fundot-io.h"

namespace fundot {
std::ostream& operator<<(std::ostream& out, const FunGetter& getter)
{
    out << getter.key << "." << getter.value;
    return out;
}

std::istream& operator>>(std::istream& in, FunList& fun_list)
{
    fun_list.clear();
    char delimiter;
    in >> delimiter;
    if (delimiter == ')') {
        return in;
    }
    in.putback(delimiter);
    Object elem;
    while (in >> elem) {
        fun_list.pushBack(elem);
        in >> delimiter;
        if (delimiter == ')') {
            return in;
        }
        in.putback(delimiter);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const FunList& fun_list)
{
    out << "( ";
    for (const Object& elem : fun_list) {
        out << elem << " ";
    }
    out << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const FunQuote& fun_quote)
{
    out << '\'' << fun_quote.value;
    return out;
}

std::ostream& operator<<(std::ostream& out, const FunSetter& setter)
{
    out << setter.key << ": " << setter.value;
    return out;
}

std::istream& operator>>(std::istream& in, String& str)
{
    str.clear();
    char c;
    in >> std::noskipws;
    while (in >> c) {
        if (c == '"') {
            in >> std::skipws;
            return in;
        }
        str.pushBack(c);
    }
    in >> std::skipws;
    return in;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    out << '"';
    for (std::size_t i = 0; i < str.size(); ++i) {
        out << str[i];
    }
    out << '"';
    return out;
}

std::istream& operator>>(std::istream& in, Symbol& symbol)
{
    static const std::unordered_set<char> delimiters = {
        ':',  '}',  ',',  ')',  ']',  ';', '.', ' ',
        '\n', '\t', '\v', '\f', '\r', '(', '[', '{'};
    symbol.clear();
    char c;
    in >> std::noskipws;
    while (in >> c) {
        if (delimiters.find(c) != delimiters.end()) {
            in.putback(c);
            break;
        }
        symbol.pushBack(c);
    }
    in >> std::skipws;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Symbol& symbol)
{
    for (std::size_t i = 0; i < symbol.size(); ++i) {
        out << symbol[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, FunSet& fun_set)
{
    fun_set.clear();
    char delimiter;
    in >> delimiter;
    if (delimiter == '}') {
        return in;
    }
    in.putback(delimiter);
    Object elem;
    while (in >> elem) {
        fun_set.emplace(elem);
        in >> delimiter;
        if (delimiter == '}') {
            return in;
        }
        in.putback(delimiter);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const FunSet& fun_set)
{
    out << "{ ";
    for (const Object& elem : fun_set) {
        out << elem << ", ";
    }
    out << "}";
    return out;
}

std::istream& operator>>(std::istream& in, FunVector& fun_vector)
{
    fun_vector.clear();
    char delimiter;
    in >> delimiter;
    if (delimiter == ']') {
        return in;
    }
    in.putback(delimiter);
    Object elem;
    while (in >> elem) {
        fun_vector.pushBack(elem);
        in >> delimiter;
        if (delimiter == ']') {
            return in;
        }
        in.putback(delimiter);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const FunVector& fun_vector)
{
    out << "[ ";
    for (const Object& elem : fun_vector) {
        out << elem << ", ";
    }
    out << "]";
    return out;
}

std::istream& operator>>(std::istream& in, Object& obj)
{
    char delimiter;
    in >> delimiter;
    if (delimiter == '\'') {
        FunQuote fun_quote;
        in >> fun_quote.value;
        obj = fun_quote;
        return in;
    }
    if (delimiter == '"') {
        String str;
        in >> str;
        obj = str;
    }
    else if (delimiter == '(') {
        FunList fun_list;
        in >> fun_list;
        obj = fun_list;
    }
    else if (delimiter == '[') {
        FunVector fun_vector;
        in >> fun_vector;
        obj = fun_vector;
    }
    else if (delimiter == '{') {
        FunSet fun_set;
        in >> fun_set;
        obj = fun_set;
    }
    else if (delimiter == ',') {
        obj = Null();
    }
    else {
        if (std::isdigit(delimiter) || delimiter == '-' || delimiter == '+') {
            in.putback(delimiter);
            Float num;
            in >> num;
            if (static_cast<Integer>(num) == num) {
                obj = static_cast<Integer>(num);
            }
            else {
                obj = num;
            }
        }
        else {
            in.putback(delimiter);
            Symbol symbol;
            in >> symbol;
            if (symbol == Symbol("true")) {
                obj = true;
            }
            else if (symbol == Symbol("false")) {
                obj = false;
            }
            else if (symbol == Symbol("null")) {
                obj = Null();
            }
            else {
                obj = symbol;
            }
        }
    }
    in >> std::noskipws >> delimiter >> std::skipws;
    if (std::isspace(delimiter)) {
        return in;
    }
    if (delimiter == ',') {
        return in;
    }
    if (delimiter == ':') {
        FunSetter fun_setter;
        fun_setter.key = obj;
        in >> fun_setter.value;
        obj = fun_setter;
        return in;
    }
    if (delimiter == '.') {
        FunGetter fun_getter;
        fun_getter.key = obj;
        in >> fun_getter.value;
        obj = fun_getter;
        return in;
    }
    in.putback(delimiter);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Object& obj)
{
    if (obj.hasType<Symbol>()) {
        out << get<const Symbol&>(obj);
    }
    else if (obj.hasType<String>()) {
        out << get<const String&>(obj);
    }
    else if (obj.hasType<Float>()) {
        out << get<const Float&>(obj);
    }
    else if (obj.hasType<Integer>()) {
        out << get<const Integer&>(obj);
    }
    else if (obj.hasType<Null>()) {
        out << "null";
    }
    else if (obj.hasType<Boolean>()) {
        out << std::boolalpha << get<const Boolean&>(obj) << std::noboolalpha;
    }
    else if (obj.hasType<FunQuote>()) {
        out << get<const FunQuote&>(obj);
    }
    else if (obj.hasType<FunList>()) {
        out << get<const FunList&>(obj);
    }
    else if (obj.hasType<FunSetter>()) {
        out << get<const FunSetter&>(obj);
    }
    else if (obj.hasType<FunGetter>()) {
        out << get<const FunGetter&>(obj);
    }
    else if (obj.hasType<FunSet>()) {
        out << get<const FunSet&>(obj);
    }
    else if (obj.hasType<FunVector>()) {
        out << get<const FunVector&>(obj);
    }
    return out;
}

}  // namespace fundot
