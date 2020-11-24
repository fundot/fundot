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

#include <iostream>
#include <string>

namespace fundot {
class String {
public:
    struct Hash {
        std::size_t operator()(const String& str) const
        {
            return std::hash<std::string>()(str.str_);
        }
    };

    String() = default;
    String(const std::string& str) : str_(str) {}

    char& operator[](std::size_t idx) { return str_[idx]; }
    char operator[](std::size_t idx) const { return str_[idx]; }

    char& back() { return str_[size() - 1]; }
    char back() const { return str_[size() - 1]; }

    std::size_t size() const { return str_.size(); }

    void clear() { str_.clear(); }
    void pushBack(char c) { str_.push_back(c); }
    void popBack() { str_.pop_back(); }

private:
    std::string str_;
};

bool operator==(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);

}  // namespace fundot

#endif
