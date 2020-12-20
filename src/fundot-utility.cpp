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

bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
    return static_cast<std::string>(lhs) < static_cast<std::string>(rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
    return static_cast<std::string>(lhs) > static_cast<std::string>(rhs);
}

bool operator<=(const String& lhs, const String& rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const String& lhs, const String& rhs)
{
    return !(lhs < rhs);
}

String operator+(const String& lhs, const String& rhs)
{
    return static_cast<std::string>(lhs) + static_cast<std::string>(rhs);
}

bool operator==(const Symbol& lhs, const Symbol& rhs)
{
    return static_cast<std::string>(lhs) == static_cast<std::string>(rhs);
}

bool operator!=(const Symbol& lhs, const Symbol& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Symbol& lhs, const Symbol& rhs)
{
    return static_cast<std::string>(lhs) < static_cast<std::string>(rhs);
}

bool operator>(const Symbol& lhs, const Symbol& rhs)
{
    return static_cast<std::string>(lhs) > static_cast<std::string>(rhs);
}

bool operator<=(const Symbol& lhs, const Symbol& rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const Symbol& lhs, const Symbol& rhs)
{
    return !(lhs < rhs);
}

Symbol operator+(const Symbol& lhs, const Symbol& rhs)
{
    return static_cast<std::string>(lhs) + static_cast<std::string>(rhs);
}

bool operator==(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Boolean>()) {
            return get<const Boolean&>(lhs) == get<const Boolean&>(rhs);
        }
        if (lhs.hasType<Null>()) {
            return true;
        }
        if (lhs.hasType<Integer>()) {
            return get<const Integer&>(lhs) == get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) == get<const Float&>(rhs);
        }
        if (lhs.hasType<Symbol>()) {
            return get<const Symbol&>(lhs) == get<const Symbol&>(rhs);
        }
        if (lhs.hasType<String>()) {
            return get<const String&>(lhs) == get<const String&>(rhs);
        }
        if (lhs.hasType<FunSetter>()) {
            return get<const FunSetter&>(lhs).key
                   == get<const FunSetter&>(rhs).key;
        }
        return false;
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) == get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return rhs == lhs;
    }
    return false;
}

bool operator!=(const Object& lhs, const Object& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Integer>()) {
            return get<const Integer&>(lhs) < get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) < get<const Float&>(rhs);
        }
        if (lhs.hasType<Symbol>()) {
            return get<const Symbol&>(lhs) < get<const Symbol&>(rhs);
        }
        if (lhs.hasType<String>()) {
            return get<const String&>(lhs) < get<const String&>(rhs);
        }
        return false;
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) < get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return get<const Float&>(lhs) < get<const Integer&>(rhs);
    }
    return lhs.type().hash_code() < rhs.type().hash_code();
}

bool operator>(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Integer>()) {
            return get<const Integer&>(lhs) > get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) > get<const Float&>(rhs);
        }
        if (lhs.hasType<Symbol>()) {
            return get<const Symbol&>(lhs) > get<const Symbol&>(rhs);
        }
        if (lhs.hasType<String>()) {
            return get<const String&>(lhs) > get<const String&>(rhs);
        }
        return false;
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) > get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return get<const Float&>(lhs) > get<const Integer&>(rhs);
    }
    return lhs.type().hash_code() > rhs.type().hash_code();
}

bool operator<=(const Object& lhs, const Object& rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const Object& lhs, const Object& rhs)
{
    return !(lhs < rhs);
}

Object operator+(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Integer>()) {
            return get<const Integer&>(lhs) + get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) + get<const Float&>(rhs);
        }
        if (lhs.hasType<Symbol>()) {
            return get<const Symbol&>(lhs) + get<const Symbol&>(rhs);
        }
        if (lhs.hasType<String>()) {
            return get<const String&>(lhs) + get<const String&>(rhs);
        }
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) + get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return get<const Float&>(lhs) + get<const Integer&>(rhs);
    }
    return Null();
}

Object operator-(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Integer>()) {
            return get<const Integer&>(lhs) - get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) - get<const Float&>(rhs);
        }
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) - get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return get<const Float&>(lhs) - get<const Integer&>(rhs);
    }
    return Null();
}

Object operator*(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Integer>()) {
            return get<const Integer&>(lhs) * get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) * get<const Float&>(rhs);
        }
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) * get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return get<const Float&>(lhs) * get<const Integer&>(rhs);
    }
    return Null();
}

Object operator/(const Object& lhs, const Object& rhs)
{
    if (lhs.type() == rhs.type()) {
        if (lhs.hasType<Integer>()) {
            return static_cast<Float>(get<const Integer&>(lhs))
                   / get<const Integer&>(rhs);
        }
        if (lhs.hasType<Float>()) {
            return get<const Float&>(lhs) / get<const Float&>(rhs);
        }
    }
    if (lhs.hasType<Integer>() && rhs.hasType<Float>()) {
        return get<const Integer&>(lhs) / get<const Float&>(rhs);
    }
    if (lhs.hasType<Float>() && rhs.hasType<Integer>()) {
        return get<const Float&>(lhs) / get<const Integer&>(rhs);
    }
    return Null();
}

Object operator%(const Object& lhs, const Object& rhs)
{
    if (lhs.hasType<Integer>() && rhs.hasType<Integer>()) {
        return get<const Integer&>(lhs) % get<const Integer&>(rhs);
    }
    return Null();
}

}  // namespace fundot
