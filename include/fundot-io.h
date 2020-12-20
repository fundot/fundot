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

#include <cstddef>
#include <iostream>
#include <unordered_set>

#include "fundot-utility.h"

namespace fundot {
std::ostream& operator<<(std::ostream& out, const FunGetter& getter);

std::istream& operator>>(std::istream& in, FunList& fun_list);
std::ostream& operator<<(std::ostream& out, const FunList& fun_list);

std::ostream& operator<<(std::ostream& out, const FunQuote& fun_quote);

std::ostream& operator<<(std::ostream& out, const FunSetter& setter);

std::istream& operator>>(std::istream& in, String& str);
std::ostream& operator<<(std::ostream& out, const String& str);

std::istream& operator>>(std::istream& in, Symbol& symbol);
std::ostream& operator<<(std::ostream& out, const Symbol& symbol);

std::istream& operator>>(std::istream& in, FunSet& fun_set);
std::ostream& operator<<(std::ostream& out, const FunSet& fun_set);

std::istream& operator>>(std::istream& in, FunVector& fun_vector);

std::ostream& operator<<(std::ostream& out, const FunVector& fun_vector);

std::istream& operator>>(std::istream& in, Object& obj);
std::ostream& operator<<(std::ostream& out, const Object& obj);

}  // namespace fundot

#endif
