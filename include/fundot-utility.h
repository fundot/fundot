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

#ifndef FUNDOT_UTILITY_H
#define FUNDOT_UTILITY_H

#include <cstdlib>
#include <string>

#include "fundot-list.h"
#include "fundot-object.h"
#include "fundot-string.h"
#include "fundot-symbol.h"
#include "fundot-unordered-set.h"
#include "fundot-vector.h"

namespace fundot {
template<typename K, typename V>
struct Getter {
    Getter(const K& init_key = K(), const V& init_value = V())
        : key(init_key), value(init_value)
    {
    }

    K key;
    mutable V value;
};

template<typename K, typename V>
struct Setter {
    Setter(const K& init_key = K(), const V& init_value = V())
        : key(init_key), value(init_value)
    {
    }

    K key;
    mutable V value;
};

template<typename T>
struct Quote {
    Quote(const T& init_value = T()) : value(init_value) {}

    T value;
};

template<typename T>
struct Hash;

struct Null {
};

using Boolean = bool;
using Float = double;
using Integer = std::int32_t;
using FunGetter = Getter<Object, Object>;
using FunList = List<Object>;
using FunQuote = Quote<Object>;
using FunSet = UnorderedSet<Object, Hash<Object>>;
using FunSetter = Setter<Object, Object>;
using FunVector = Vector<Object>;

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);

String operator+(const String& lhs, const String& rhs);

bool operator==(const Symbol& lhs, const Symbol& rhs);
bool operator!=(const Symbol& lhs, const Symbol& rhs);
bool operator<(const Symbol& lhs, const Symbol& rhs);
bool operator>(const Symbol& lhs, const Symbol& rhs);
bool operator<=(const Symbol& lhs, const Symbol& rhs);
bool operator>=(const Symbol& lhs, const Symbol& rhs);

Symbol operator+(const Symbol& lhs, const Symbol& rhs);

bool operator==(const Object& lhs, const Object& rhs);
bool operator!=(const Object& lhs, const Object& rhs);
bool operator<(const Object& lhs, const Object& rhs);
bool operator>(const Object& lhs, const Object& rhs);
bool operator<=(const Object& lhs, const Object& rhs);
bool operator>=(const Object& lhs, const Object& rhs);

Object operator+(const Object& lhs, const Object& rhs);
Object operator-(const Object& lhs, const Object& rhs);
Object operator*(const Object& lhs, const Object& rhs);
Object operator/(const Object& lhs, const Object& rhs);
Object operator%(const Object& lhs, const Object& rhs);

}  // namespace fundot

#include "fundot-utility.hpp"

#endif
