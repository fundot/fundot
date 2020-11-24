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

#include "../include/fundot-io.h"

namespace fundot {
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
    for (std::size_t i = 0; i < str.size(); ++i) { out << str[i]; }
    out << '"';
    return out;
}

std::istream& operator>>(std::istream& in, Symbol& symbol)
{
    static const std::unordered_set<char> delimiters = {':', '}', ','};
    symbol.clear();
    std::string ident;
    in >> ident;
    symbol = ident;
    if (delimiters.find(symbol.back()) != delimiters.end()) {
        in.putback(symbol.back());
        symbol.popBack();
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Symbol& symbol)
{
    for (std::size_t i = 0; i < symbol.size(); ++i) { out << symbol[i]; }
    return out;
}

}  // namespace fundot
