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

#ifndef FUNDOT_SYMBOL_H
#define FUNDOT_SYMBOL_H

#include <cstddef>
#include <string>

namespace fundot {
class Symbol {
public:
    Symbol() = default;
    Symbol(std::string&& str) : ident_(std::move(str)) {}

    explicit operator std::string() const { return ident_; }
    explicit operator const std::string&() const { return ident_; }

    char& operator[](std::size_t idx) { return ident_[idx]; }
    char operator[](std::size_t idx) const { return ident_[idx]; }

    char& back() { return ident_.back(); }
    char back() const { return ident_.back(); }

    bool empty() const { return ident_.empty(); }
    std::size_t size() const { return ident_.size(); }

    void clear() { ident_.clear(); }
    void pushBack(char c) { ident_.push_back(c); }
    void popBack() { ident_.pop_back(); }

private:
    std::string ident_;
};

}  // namespace fundot

#endif
