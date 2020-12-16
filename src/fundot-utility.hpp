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

template<>
struct Hash<String> {
    std::size_t operator()(const String& str) const
    {
        return std::hash<std::string>{}(static_cast<std::string>(str));
    }
};

template<>
struct Hash<Symbol> {
    std::size_t operator()(const Symbol& symbol) const
    {
        return std::hash<std::string>{}(static_cast<std::string>(symbol));
    }
};

template<>
struct Hash<Object> {
    std::size_t operator()(const Object& obj) const
    {
        if (obj.hasType<Symbol>()) {
            return Hash<Symbol>{}(get<const Symbol&>(obj));
        }
        if (obj.hasType<String>()) {
            return Hash<String>{}(get<const String&>(obj));
        }
        return 0;
    }
};

template<>
struct Hash<FunSetter> {
    std::size_t operator()(const FunSetter& setter) const
    {
        return Hash<Object>{}(setter.key);
    }
};

}  // namespace fundot
