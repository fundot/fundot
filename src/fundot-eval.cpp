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

#include "fundot-eval.h"

namespace fundot {
Object eval(const FunSetter& fun_setter, FunSet& scope)
{
    scope.emplace(fun_setter);
    return fun_setter;
}

Object eval(const Symbol& symbol, FunSet& scope)
{
    FunSetter to_find;
    to_find.key = symbol;
    FunSet::Iterator it = scope.find(to_find);
    if (it != scope.end() && it->hasType<FunSetter>()) {
        return static_cast<FunSetter>(*it).value;
    }
    return symbol;
}

Object eval(const FunList& fun_list, FunSet& scope)
{
    FunList after_eval;
    FunList::ConstIterator it = fun_list.begin();
    while (it != fun_list.end()) {
        after_eval.pushBack(eval(*it, scope));
        ++it;
    }
    it = fun_list.begin();
    if (*it++ == Symbol("add")) {
        Float first = 0;
        if (it->hasType<Float>()) {
            first = static_cast<Float>(*it++);
        }
        else if (it->hasType<Integer>()) {
            first = static_cast<Integer>(*it++);
        }
        Float second = 0;
        if (it->hasType<Float>()) {
            second = static_cast<Float>(*it);
        }
        else if (it->hasType<Integer>()) {
            second = static_cast<Integer>(*it);
        }
        return first + second;
    }
    return after_eval;
}

Object eval(const Object& obj, FunSet& scope)
{
    if (obj.hasType<FunSetter>()) {
        return eval(static_cast<FunSetter>(obj), scope);
    }
    if (obj.hasType<Symbol>()) {
        return eval(static_cast<Symbol>(obj), scope);
    }
    if (obj.hasType<FunList>()) {
        return eval(static_cast<FunList>(obj), scope);
    }
    return obj;
}

}  // namespace fundot
