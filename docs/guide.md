# Fundot Beginner's Guide

This is a tutorial for Fundot beginners.

## Introduction

Fundot is a functional programming language inspired by Lisp. However, Fundot uses capital letters, "A" to "Z", and dot, ".", as we normally do in English,
to indicate the start and end of a function, instead of using parenthesis, "(" and ")",
which is a big difference between Fundot and Lisp. This feature also makes Fundot more readable.

## Basic Syntax

* Each function call starts from a name with uppercase initial and reads arguments until a word that ends with dot appears.

A code that returns the sum of 1 and 2, which is 3, is shown below:

    Num+ 1 2.

* Calling functions as arguments inside a function is allowed in Fundot.

Therefore, the following code returns the sum of the sum of 1 and 2 and the sum of 1 and 2, which is 6.

    Num+ Num+ 1 2. Num+ 1 2..

* Whitespace, tab, and newline have no effect on Fundot code.

Therefore, we can also write the above code in the following way:

    Num+
        Num+ 1 2.
        Num+ 1 2..
This is a more preferring way of writing Fundot code,
because it seems to be clearer on what arguments we pass to a function.

* To define a variable or function, we use Def function. The first argument we pass to Def is treated as the name of the function, the arguments before and including the first one that ends with dot, if any, are treated as the function's arguments, and the arguments after that are treated as the function's body.

For example, we can define an alias of Num+ in the following way:

    Def Sum-of-two-numbers a b. Num+ a b..
Because variables and functions are similar in Fundot, a variable is defined in the same way:

    Def x 1.
The above code actually defines a function named "a" with a body "1", but since all names of Fundot functions should have capital letters as their initials, such definition defines a variable.

Therefore, we can rewrite the last example of the above style as below:

    Def Sum-of-two-numbers a b. Num+ a b..
    Def x 1.
    Sum-of-two-numbers x
        Sum-of-two-numbers x
            Sum-of-two-numbers
                Sum-of-two-numbers x 2.
                Sum-of-two-numbers x 2....
