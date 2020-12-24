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

#ifndef FUNDOT_STRING_H
#define FUNDOT_STRING_H

#include <cstddef>
#include <string>

namespace fundot {
class String {
public:
    String() = default;
    String(std::string&& str) : str_(std::move(str)) {}

    explicit operator std::string() const { return str_; }
    explicit operator const std::string&() const { return str_; }

    char& operator[](std::size_t idx) { return str_[idx]; }
    char operator[](std::size_t idx) const { return str_[idx]; }

    char& back() { return str_.back(); }
    char back() const { return str_.back(); }

    bool empty() const { return str_.empty(); }
    std::size_t size() const { return str_.size(); }

    void clear() { str_.clear(); }
    void pushBack(char c) { str_.push_back(c); }
    void popBack() { str_.pop_back(); }

private:
    std::string str_;
};

}  // namespace fundot

#endif
