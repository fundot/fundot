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
Object builtInQuote(const FunList& fun_list)
{
    return *(++fun_list.begin());
}

Object builtInQuit(const FunList& fun_list)
{
    exit(EXIT_SUCCESS);
    return fun_list;
}

Object builtInIf(const FunList& fun_list)
{
    FunList::ConstIterator iter = fun_list.begin();
    if ((++iter)->hasType<Null>() || *iter == Boolean(false)) {
        if (++iter != fun_list.end() && ++iter != fun_list.end()) {
            return *iter;
        }
        return Null();
    }
    if (++iter != fun_list.end()) {
        return *iter;
    }
    return fun_list;
}

Object builtInCond(const FunList& fun_list)
{
    FunList::ConstIterator iter = fun_list.begin();
    while (++iter != fun_list.end()) {}
    if ((++iter)->hasType<Null>() || *iter == Boolean(false)) {
        if (++iter != fun_list.end() && ++iter != fun_list.end()) {
            return *iter;
        }
        return Null();
    }
    if (++iter != fun_list.end()) {
        return *iter;
    }
    return fun_list;
}

Object builtInAdd(const FunList& fun_list)
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

Object builtInMul(const FunList& fun_list)
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
    return first * second;
}

Object Evaluator::operator()(const Object& obj)
{
    return eval(obj);
}

Object Evaluator::eval(const FunSetter& fun_setter)
{
    fun_setter.value = eval(fun_setter.value);
    scope_.erase(fun_setter);
    scope_.emplace(fun_setter);
    return fun_setter;
}

Object Evaluator::eval(const Symbol& symbol)
{
    FunSetter to_find;
    to_find.key = symbol;
    FunSet::Iterator it = scope_.find(to_find);
    if (it != scope_.end() && it->hasType<FunSetter>()) {
        return eval(static_cast<FunSetter>(*it).value);
    }
    return symbol;
}

Object Evaluator::eval(const FunGetter& fun_getter)
{
    Object key_after_eval = eval(fun_getter.key);
    if (key_after_eval.hasType<FunSet>()) {
        Evaluator next_eval(static_cast<FunSet>(key_after_eval));
        return next_eval(fun_getter.value);
    }
    return fun_getter;
}

Object Evaluator::eval(const FunList& fun_list)
{
    static std::unordered_map<Object, std::function<Object(const FunList&)>,
                              Hash<Object>>
        built_in_macros = {{Symbol("quote"), builtInQuote},
                           {Symbol("quit"), builtInQuit},
                           {Symbol("if"), builtInIf}};
    if (built_in_macros.find(fun_list.front()) != built_in_macros.end()) {
        return eval(built_in_macros[fun_list.front()](fun_list));
    }
    FunList after_eval;
    FunList::ConstIterator it = fun_list.begin();
    while (it != fun_list.end()) {
        after_eval.pushBack(eval(*it++));
    }
    static std::unordered_map<Object, std::function<Object(const FunList&)>,
                              Hash<Object>>
        built_in_functions = {{Symbol("add"), builtInAdd},
                              {Symbol("mul"), builtInMul}};
    if (built_in_functions.find(fun_list.front()) != built_in_functions.end()) {
        return built_in_functions[fun_list.front()](fun_list);
    }
    return after_eval;
}

Object Evaluator::eval(const FunVector& fun_vector)
{
    FunVector after_eval;
    for (const Object& obj : fun_vector) {
        after_eval.pushBack(eval(obj));
    }
    return after_eval;
}

Object Evaluator::eval(const Object& obj)
{
    if (obj.hasType<FunSetter>()) {
        return eval(static_cast<FunSetter>(obj));
    }
    if (obj.hasType<Symbol>()) {
        return eval(static_cast<Symbol>(obj));
    }
    if (obj.hasType<FunGetter>()) {
        return eval(static_cast<FunGetter>(obj));
    }
    if (obj.hasType<FunList>()) {
        return eval(static_cast<FunList>(obj));
    }
    if (obj.hasType<FunVector>()) {
        return eval(static_cast<FunVector>(obj));
    }
    return obj;
}

}  // namespace fundot
