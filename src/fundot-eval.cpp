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

Object Evaluator::builtInLambda(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    FunSet function;
    function.emplace(FunSetter(Symbol("type"), Symbol("function")));
    function.emplace(FunSetter(Symbol("params"), *iter));
    function.emplace(FunSetter(Symbol("body"), *(++iter)));
    return function;
}

Object Evaluator::builtInDefun(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    Symbol name(*iter);
    FunList lambda;
    lambda.pushBack(Symbol("lambda"));
    while (++iter != fun_list.end()) {
        lambda.pushBack(*iter);
    }
    return eval(FunSetter(name, eval(lambda)));
}

Object Evaluator::builtInIf(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    Object result = eval(*iter);
    if (result.hasType<Null>() || result == Boolean(false)) {
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
        Object result = eval(*iter);
        ++iter;
        if (result.hasType<Null>() == false && result != Boolean(false)) {
            return *iter;
        }
    }
    return Null();
}

Object Evaluator::builtInWhile(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    Object predicate = *iter;
    Object to_eval = *(++iter);
    Object result = eval(predicate);
    Object ret = Null();
    while (result.hasType<Null>() == false && result != Boolean(false)) {
        ret = eval(to_eval);
        result = eval(predicate);
    }
    return ret;
}

Object Evaluator::builtInGlobal(const FunList& fun_list)
{
    return scope_;
    return fun_list;
}

Object Evaluator::builtInScan(const FunList& fun_list)
{
    Object ret;
    in_ >> ret;
    return ret;
    return fun_list;
}

Object Evaluator::builtInPrint(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    if (iter != fun_list.end()) {
        out_ << *iter << "\n";
    }
    return *iter;
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
        const FunVector& fun_vector = get<const FunVector&>(*iter);
        if ((++iter)->hasType<Integer>()
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

Object Evaluator::builtInEqual(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter == *(++iter);
}

Object Evaluator::builtInNotEqual(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter != *(++iter);
}

Object Evaluator::builtInLessThan(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter < *(++iter);
}

Object Evaluator::builtInGreaterThan(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter > *(++iter);
}

Object Evaluator::builtInLessThanOrEqual(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter <= *(++iter);
}

Object Evaluator::builtInGreaterThanOrEqual(const FunList& fun_list)
{
    FunList::ConstIterator iter = ++fun_list.begin();
    return *iter >= *(++iter);
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
    FunSetter setter(fun_setter.key, eval(fun_setter.value));
    scope_.erase(setter);
    scope_.emplace(setter);
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
            if (it == scope_ptr->end() || it->hasType<FunSetter>() == false) {
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
                           {Symbol("lambda"), &Evaluator::builtInLambda},
                           {Symbol("defun"), &Evaluator::builtInDefun},
                           {Symbol("if"), &Evaluator::builtInIf},
                           {Symbol("cond"), &Evaluator::builtInCond},
                           {Symbol("while"), &Evaluator::builtInWhile}};
    if (built_in_macros.find(fun_list.front()) != built_in_macros.end()) {
        return eval(built_in_macros[fun_list.front()](this, fun_list));
    }
    FunList after_eval;
    FunList::ConstIterator iter = fun_list.begin();
    while (iter != fun_list.end()) {
        after_eval.pushBack(eval(*iter));
        ++iter;
    }
    static std::unordered_map<
        Object, std::function<Object(Evaluator*, const FunList&)>, Hash<Object>>
        built_in_functions = {
            {Symbol("global"), &Evaluator::builtInGlobal},
            {Symbol("scan"), &Evaluator::builtInScan},
            {Symbol("print"), &Evaluator::builtInPrint},
            {Symbol("get"), &Evaluator::builtInGet},
            {Symbol("add"), &Evaluator::builtInAdd},
            {Symbol("sub"), &Evaluator::builtInSub},
            {Symbol("mul"), &Evaluator::builtInMul},
            {Symbol("div"), &Evaluator::builtInDiv},
            {Symbol("mod"), &Evaluator::builtInMod},
            {Symbol("comp="), &Evaluator::builtInEqual},
            {Symbol("comp!="), &Evaluator::builtInNotEqual},
            {Symbol("comp<"), &Evaluator::builtInLessThan},
            {Symbol("comp>"), &Evaluator::builtInGreaterThan},
            {Symbol("comp<="), &Evaluator::builtInLessThanOrEqual},
            {Symbol("comp>="), &Evaluator::builtInGreaterThanOrEqual}};
    if (built_in_functions.find(after_eval.front())
        != built_in_functions.end()) {
        return built_in_functions[after_eval.front()](this, after_eval);
    }
    if (after_eval.front().hasType<FunSet>()) {
        const FunSet& function = get<const FunSet&>(after_eval.front());
        FunSet::ConstIterator it = function.find(FunSetter(Symbol("type")));
        if (it != function.end()
            && get<const FunSetter&>(*it).value == Symbol("function")) {
            FunSet local = scope_;
            Evaluator local_eval(local, in_, out_);
            it = function.find(FunSetter(Symbol("params")));
            if (it != function.end()) {
                const Object& body = get<const FunSetter&>(*it).value;
                if (body.hasType<FunList>()) {
                    const FunList& params = get<const FunList&>(body);
                    FunList::ConstIterator param_iter = params.begin();
                    FunList::Iterator arg_iter = ++after_eval.begin();
                    while (param_iter != params.end()
                           && arg_iter != after_eval.end()) {
                        local_eval(FunSetter(*param_iter, *arg_iter));
                        ++param_iter;
                        ++arg_iter;
                    }
                }
            }
            Object to_eval;
            it = function.find(FunSetter(Symbol("body")));
            if (it != function.end()) {
                to_eval = get<const FunSetter&>(*it).value;
            }
            else {
                to_eval = Null();
            }
            return local_eval(to_eval);
        }
    }
    return after_eval;
}

Object Evaluator::eval(const FunVector& fun_vector)
{
    FunVector after_eval;
    for (const Object& obj : fun_vector) {
        after_eval.pushBack(eval(obj));
    }
    return after_eval.back();
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
