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

#ifndef FUNDOT_IO_H
#define FUNDOT_IO_H

#include <string>
#include <unordered_set>

#include "fundot-pair.h"
#include "fundot-string.h"
#include "fundot-symbol.h"
#include "fundot-unordered-set.h"

namespace fundot {
template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const Pair<T, U>& pr)
{
    out << pr.left << ": " << pr.right;
    return out;
}

std::istream& operator>>(std::istream& in, String& str);
std::ostream& operator<<(std::ostream& out, const String& str);

std::istream& operator>>(std::istream& in, Symbol& symbol);
std::ostream& operator<<(std::ostream& out, const Symbol& symbol);

template<typename T, typename Hash = std::hash<T>>
std::istream& operator>>(std::istream& in, UnorderedSet<T, Hash>& ust)
{
    ust.clear();
    char delimiter;
    T elem;
    while (in >> elem) {
        ust.emplace(elem);
        in >> delimiter;
        if (delimiter == '}') {
            return in;
        }
    }
    return in;
}

template<typename T, typename Hash = std::hash<T>>
std::ostream& operator<<(std::ostream& out, const UnorderedSet<T, Hash>& ust)
{
    out << "{\n";
    for (const T& elem : ust) { out << "    " << elem << ",\n"; }
    out << "}";
    return out;
}

}  // namespace fundot

#endif
