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

#include "fundot-utility.h"

namespace fundot {
class Evaluator {
public:
    Evaluator(FunSet& scope) : scope_(scope) {}

    Object& operator()(Object& obj);

private:
    FunSet& scope_;

    Object& builtInQuit(FunList& fun_list);

    Object& builtInIf(FunList& fun_list);

    Object& builtInCond(FunList& fun_list);

    Object& builtInWhile(FunList& fun_list);

    Object& builtInAdd(FunList& fun_list);

    Object& builtInMul(FunList& fun_list);

    Object& eval(FunQuote& fun_quote);

    Object& eval(FunSetter& fun_setter);

    Object& eval(Symbol& symbol);

    Object& eval(FunGetter& fun_getter);

    Object& eval(FunList& fun_list);

    Object& eval(FunVector& fun_vector);

    Object& eval(Object& obj);

    Object& eval(const Object& obj);
};

}  // namespace fundot

#endif
