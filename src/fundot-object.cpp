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

#include "../include/fundot-object.h"

namespace fundot {
std::istream& operator>>(std::istream& in, Object& obj)
{
    char delimiter;
    in >> delimiter;
    if (delimiter == '"') {
        String str;
        in >> str;
        obj = str;
        return in;
    }
    if (delimiter == '{') {
        FunSet fun_set;
        in >> fun_set;
        obj = fun_set;
        return in;
    }
    in.putback(delimiter);
    Symbol symbol;
    in >> symbol;
    in >> delimiter;
    if (delimiter == ':') {
        FunPair fun_pair;
        fun_pair.left = symbol;
        in >> fun_pair.right;
        obj = fun_pair;
        return in;
    }
    in.putback(delimiter);
    obj = symbol;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Object& obj)
{
    if (obj.hasType<Symbol>()) {
        out << obj.cast<Symbol>();
    }
    else if (obj.hasType<String>()) {
        out << obj.cast<String>();
    }
    else if (obj.hasType<FunPair>()) {
        out << obj.cast<FunPair>();
    }
    else if (obj.hasType<FunSet>()) {
        out << obj.cast<FunSet>();
    }
    return out;
}

bool operator==(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Symbol>()) {
            return lhs.cast<Symbol>() == rhs.cast<Symbol>();
        }
        if (lhs.hasType<String>()) {
            return lhs.cast<String>() == rhs.cast<String>();
        }
        return false;
    }
    return false;
}

bool operator<(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Symbol>()) {
            return lhs.cast<Symbol>() < rhs.cast<Symbol>();
        }
        if (lhs.hasType<String>()) {
            return lhs.cast<String>() < rhs.cast<String>();
        }
        return false;
    }
    return lhs.type().hash_code() < rhs.type().hash_code();
}

std::size_t Object::Hash::operator()(const Object& obj) const
{
    if (obj.hasType<Symbol>()) {
        return Symbol::Hash()(obj.cast<Symbol>());
    }
    if (obj.hasType<String>()) {
        return String::Hash()(obj.cast<String>());
    }
    return 0;
}

}  // namespace fundot
