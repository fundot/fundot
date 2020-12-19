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
Object Evaluator::builtInQuit(const FunList& fun_list)
{
    exit(EXIT_SUCCESS);
    return fun_list;
}

Object Evaluator::builtInIf(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    Object predicate = eval(*iter);
    if (predicate.hasType<Null>() || predicate == Boolean(false)) {
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

Object Evaluator::builtInCond(const FunList& fun_list)
{
    FunList::ConstIterator iter = fun_list.begin();
    while (++iter != fun_list.end()) {
        Object predicate = eval(*iter++);
        if (predicate.hasType<Null>() == false && predicate != Boolean(false)) {
            return *iter;
        }
    }
    return Null();
}

Object Evaluator::builtInWhile(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    FunList::ConstIterator predicate_iter = iter;
    Object predicate = eval(*iter++);
    Object to_eval = *iter;
    while (predicate.hasType<Null>() == false && predicate != Boolean(false)) {
        eval(to_eval);
        predicate = eval(*predicate_iter);
    }
    return Null();
}

Object Evaluator::builtInGlobal(const FunList& fun_list)
{
    return scope_;
    return fun_list;
}

Object Evaluator::builtInGet(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    if (iter->hasType<FunSet>()) {
        const FunSet& fun_set = get<const FunSet&>(*iter);
        FunSet::ConstIterator it = fun_set.find(FunSetter(*(++iter)));
        if (it != fun_set.end() && it->hasType<FunSetter>()) {
            return get<const FunSetter&>(*it).value;
        }
    }
    if (iter->hasType<FunVector>()) {
        const FunVector& fun_vector = get<const FunVector&>(*iter++);
        if (iter->hasType<Integer>()
            && static_cast<std::size_t>(get<const Integer&>(*iter))
                   < fun_vector.size()) {
            return fun_vector[get<const Integer&>(*iter)];
        }
        return Null();
    }
    return fun_list;
}

Object Evaluator::builtInAdd(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter + *(++iter);
}

Object Evaluator::builtInSub(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter - *(++iter);
}

Object Evaluator::builtInMul(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter * *(++iter);
}

Object Evaluator::builtInDiv(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter / *(++iter);
}

Object Evaluator::builtInMod(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter % *(++iter);
}

Object Evaluator::operator()(const Object& obj)
{
    return eval(obj);
}

Object Evaluator::eval(const FunQuote& fun_quote)
{
    return fun_quote.value;
}

Object Evaluator::eval(const FunSetter& fun_setter)
{
    fun_setter.value = eval(fun_setter.value);
    scope_.erase(fun_setter);
    scope_.emplace(fun_setter);
    return get<const FunSetter&>(*scope_.find(fun_setter)).value;
}

Object Evaluator::eval(const Symbol& symbol)
{
    FunSet::Iterator it = scope_.find(FunSetter(symbol));
    if (it != scope_.end() && it->hasType<FunSetter>()) {
        return eval(get<const FunSetter&>(*it).value);
    }
    return symbol;
}

Object Evaluator::eval(const FunGetter& fun_getter)
{
    FunSet* scope_ptr = &scope_;
    FunGetter getter = fun_getter;
    while (scope_ptr != nullptr) {
        if (getter.key.hasType<Symbol>()) {
            FunSet::Iterator it = scope_ptr->find(FunSetter(getter.key));
            if (it->hasType<FunSetter>() == false) {
                return Null();
            }
            Object& value = get<const FunSetter&>(*it).value;
            if (value.hasType<FunSet>() == false) {
                return Null();
            }
            scope_ptr = get<FunSet>(&value);
            if (getter.value.hasType<Symbol>()) {
                it = scope_ptr->find(FunSetter(getter.value));
                if (it != scope_ptr->end() && it->hasType<FunSetter>()) {
                    return eval(get<const FunSetter&>(*it).value);
                }
                return Null();
            }
            if (fun_getter.value.hasType<FunSetter>()) {
                FunSetter setter = get<const FunSetter&>(fun_getter.value);
                setter.value = eval(setter.value);
                scope_ptr->erase(setter);
                scope_ptr->emplace(setter);
                return get<const FunSetter&>(*scope_ptr->find(setter)).value;
            }
            if (getter.value.hasType<FunGetter>()) {
                getter = get<const FunGetter&>(fun_getter.value);
            }
        }
    }
    return fun_getter;
}

Object Evaluator::eval(const FunList& fun_list)
{
    static std::unordered_map<
        Object, std::function<Object(Evaluator*, const FunList&)>, Hash<Object>>
        built_in_macros = {{Symbol("quit"), &Evaluator::builtInQuit},
                           {Symbol("if"), &Evaluator::builtInIf},
                           {Symbol("cond"), &Evaluator::builtInCond},
                           {Symbol("while"), &Evaluator::builtInWhile}};
    if (built_in_macros.find(fun_list.front()) != built_in_macros.end()) {
        return eval(built_in_macros[fun_list.front()](this, fun_list));
    }
    FunList after_eval;
    FunList::ConstIterator it = fun_list.begin();
    while (it != fun_list.end()) {
        after_eval.pushBack(eval(*it++));
    }
    static std::unordered_map<
        Object, std::function<Object(Evaluator*, const FunList&)>, Hash<Object>>
        built_in_functions = {{Symbol("global"), &Evaluator::builtInGlobal},
                              {Symbol("get"), &Evaluator::builtInGet},
                              {Symbol("add"), &Evaluator::builtInAdd},
                              {Symbol("sub"), &Evaluator::builtInSub},
                              {Symbol("mul"), &Evaluator::builtInMul},
                              {Symbol("div"), &Evaluator::builtInDiv},
                              {Symbol("mod"), &Evaluator::builtInMod}};
    if (built_in_functions.find(after_eval.front())
        != built_in_functions.end()) {
        return built_in_functions[after_eval.front()](this, after_eval);
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
    if (obj.hasType<FunQuote>()) {
        return eval(get<const FunQuote&>(obj));
    }
    if (obj.hasType<FunSetter>()) {
        return eval(get<const FunSetter&>(obj));
    }
    if (obj.hasType<Symbol>()) {
        return eval(get<const Symbol&>(obj));
    }
    if (obj.hasType<FunGetter>()) {
        return eval(get<const FunGetter&>(obj));
    }
    if (obj.hasType<FunList>()) {
        return eval(get<const FunList&>(obj));
    }
    if (obj.hasType<FunVector>()) {
        return eval(get<const FunVector&>(obj));
    }
    return obj;
}

}  // namespace fundot
