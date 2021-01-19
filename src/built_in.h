#ifndef FUNDOT_BUILT_IN_H
#define FUNDOT_BUILT_IN_H

#include <iostream>

#include "types.h"

namespace fundot {

Object if_(Evaluator* eval, const List& list);

Object cond_(Evaluator* eval, const List& list);

Object while_(Evaluator* eval, const List& list);

Object lambda_(const List& list);

Object defun_(Evaluator* eval, const List& list);

Object quit_();

Object eval_(Evaluator* eval, const List& list);

Object read_(const List& list);

Object print_(const List& list);

Object open_(const List& list);

Object close_(const List& list);

Object do_(const List& list);

Object count_(const List& list);

Object append_(const List& list);

Object insert_(const List& list);

Object remove_(const List& list);

Object pop_(const List& list);

}  // namespace fundot

#endif
