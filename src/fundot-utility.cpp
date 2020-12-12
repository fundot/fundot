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

#include "fundot-utility.h"

namespace fundot {
bool operator==(const String& lhs, const String& rhs)
{
    return static_cast<std::string>(lhs) == static_cast<std::string>(rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
    return static_cast<std::string>(lhs) < static_cast<std::string>(rhs);
}

bool operator==(const Symbol& lhs, const Symbol& rhs)
{
    return static_cast<std::string>(lhs) == static_cast<std::string>(rhs);
}

bool operator<(const Symbol& lhs, const Symbol& rhs)
{
    return static_cast<std::string>(lhs) < static_cast<std::string>(rhs);
}

bool operator==(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Boolean>()) {
            return static_cast<Boolean>(lhs) == static_cast<Boolean>(rhs);
        }
        if (lhs.hasType<Symbol>()) {
            return static_cast<Symbol>(lhs) == static_cast<Symbol>(rhs);
        }
        if (lhs.hasType<String>()) {
            return static_cast<String>(lhs) == static_cast<String>(rhs);
        }
        if (lhs.hasType<FunSetter>()) {
            return static_cast<FunSetter>(lhs).key
                   == static_cast<FunSetter>(rhs).key;
        }
        return false;
    }
    return false;
}

bool operator<(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Symbol>()) {
            return static_cast<Symbol>(lhs) < static_cast<Symbol>(rhs);
        }
        if (lhs.hasType<String>()) {
            return static_cast<String>(lhs) < static_cast<String>(rhs);
        }
        return false;
    }
    return lhs.type().hash_code() < rhs.type().hash_code();
}

}  // namespace fundot
