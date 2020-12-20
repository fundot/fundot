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

#ifndef FUNDOT_EVAL_H
#define FUNDOT_EVAL_H

#include <functional>
#include <unordered_map>

#include "fundot-io.h"
#include "fundot-utility.h"

namespace fundot {
class Evaluator {
public:
    Evaluator(FunSet& scope, std::istream& in = std::cin,
              std::ostream& out = std::cout)
        : scope_(scope), in_(in), out_(out)
    {
    }

    Object operator()(const Object& obj);

private:
    FunSet& scope_;

    std::istream& in_;

    std::ostream& out_;

    Object builtInQuit(const FunList& fun_list);

    Object builtInLambda(const FunList& fun_list);

    Object builtInDefun(const FunList& fun_list);

    Object builtInIf(const FunList& fun_list);

    Object builtInCond(const FunList& fun_list);

    Object builtInWhile(const FunList& fun_list);

    Object builtInGlobal(const FunList& fun_list);

    Object builtInScan(const FunList& fun_list);

    Object builtInPrint(const FunList& fun_list);

    Object builtInGet(const FunList& fun_list);

    Object builtInAdd(const FunList& fun_list);

    Object builtInSub(const FunList& fun_list);

    Object builtInMul(const FunList& fun_list);

    Object builtInDiv(const FunList& fun_list);

    Object builtInMod(const FunList& fun_list);

    Object builtInEqual(const FunList& fun_list);

    Object builtInNotEqual(const FunList& fun_list);

    Object builtInLessThan(const FunList& fun_list);

    Object builtInGreaterThan(const FunList& fun_list);

    Object builtInLessThanOrEqual(const FunList& fun_list);

    Object builtInGreaterThanOrEqual(const FunList& fun_list);

    Object eval(const FunQuote& fun_quote);

    Object eval(const FunSetter& fun_setter);

    Object eval(const Symbol& symbol);

    Object eval(const FunGetter& fun_getter);

    Object eval(const FunList& fun_list);

    Object eval(const FunVector& fun_vector);

    Object eval(const Object& obj);
};

}  // namespace fundot

#endif
