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
Object quit(const FunList& fun_list)
{
    exit(EXIT_SUCCESS);
    return fun_list;
}

Object add(const FunList& fun_list)
{
    FunList::ConstIterator iter = fun_list.begin();
    Float first = 0;
    if ((++iter)->hasType<Float>()) {
        first = static_cast<Float>(*iter);
    }
    else if (iter->hasType<Integer>()) {
        first = static_cast<Integer>(*iter);
    }
    Float second = 0;
    if ((++iter)->hasType<Float>()) {
        second = static_cast<Float>(*iter);
    }
    else if (iter->hasType<Integer>()) {
        second = static_cast<Integer>(*iter);
    }
    return first + second;
}

Object eval(const FunSetter& fun_setter, FunSet& scope)
{
    fun_setter.value = eval(fun_setter.value, scope);
    scope.erase(fun_setter);
    scope.emplace(fun_setter);
    return fun_setter;
}

Object eval(const Symbol& symbol, FunSet& scope)
{
    FunSetter to_find;
    to_find.key = symbol;
    FunSet::Iterator it = scope.find(to_find);
    if (it != scope.end() && it->hasType<FunSetter>()) {
        return eval(static_cast<FunSetter>(*it).value, scope);
    }
    return symbol;
}

Object eval(const FunGetter& fun_getter, FunSet& scope)
{
    Object key_after_eval = eval(fun_getter.key, scope);
    if (key_after_eval.hasType<FunSet>()) {
        FunSet next_set = static_cast<FunSet>(key_after_eval);
        return eval(fun_getter.value, next_set);
    }
    return fun_getter;
}

Object eval(const FunList& fun_list, FunSet& scope)
{
    if (fun_list.front() == Symbol("quote")) {
        return *(++fun_list.begin());
    }
    FunList after_eval;
    FunList::ConstIterator it = fun_list.begin();
    while (it != fun_list.end()) { after_eval.pushBack(eval(*it++, scope)); }
    static std::unordered_map<Object,
                              std::function<Object(const FunList&)>,
                              Hash<Object>>
        built_in_functions = {{Symbol("quit"), quit}, {Symbol("add"), add}};
    if (built_in_functions.find(fun_list.front()) != built_in_functions.end()) {
        return built_in_functions[fun_list.front()](fun_list);
    }
    return after_eval;
}

Object eval(const FunVector& fun_vector, FunSet& scope)
{
    FunVector after_eval;
    for (const Object& obj : fun_vector) {
        after_eval.pushBack(eval(obj, scope));
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
    if (obj.hasType<FunGetter>()) {
        return eval(static_cast<FunGetter>(obj), scope);
    }
    if (obj.hasType<FunList>()) {
        return eval(static_cast<FunList>(obj), scope);
    }
    if (obj.hasType<FunVector>()) {
        return eval(static_cast<FunVector>(obj), scope);
    }
    return obj;
}

}  // namespace fundot
