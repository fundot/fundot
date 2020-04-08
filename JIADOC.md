# Jia Documentation

This is the official documentation for Jia programming language.

## Introduction

Jia is a functional programming language inspired by Lisp. However, Jia uses capital letters, "A" to "Z", and dot, ".", as we normally do in English,
to indicate the start and end of a function, instead of using parenthesis, "(" and ")",
which is a big difference between Jia and Lisp.

## Basic Syntax

* Each function call starts from a name with uppercase initial and reads arguments until a word that ends with dot appears.

A code that returns the sum of 1 and 2, which is 3, is shown below:

    Add 1 2.

* Recursion is allowed in Jia.

Therefore, the following code returns the sum of the sum of 1 and 2 and the sum of 1 and 2, which is 6.

    Add Add 1 2. Add 1 2..

* Whitespace, tab, and newline have no effect on Jia code.

Therefore, we can also write the above code in the following way:

    Add
        Add 1 2.
        Add 1 2..
This is a more preferring way of writing Jia code,
because it seems to be clearer on what arguments we pass to a function.

Another example that demonstrates the above style is shown below:

    Add 1
        Add 1
            Add
                Add 1 2.
                Add 1 2....
In a word, each time we want to call a function in another function, we enter a newline and indent.

* To define a variable or function, we use Def function. The first argument we pass to Def is treated as the name of the function, the arguments before and including the first one that ends with dot, if any, are treated as the function's arguments, and the arguments after that are treated as the function's body.

For example, we can define an alias of Add in the following way:

    Def Sum-of-two-numbers a b. Add a b..
Because variables and functions are similar in Jia, a variable is defined in the same way:

    Def x 1.
The above code actually defines a function named "a" with a body "1", but since all names of Jia functions should have capital letters as their initials, such definition defines a variable.

Therefore, we can rewrite the last example of the above style as below:

    Def Sum-of-two-numbers a b. Add a b..
    Def x 1.
    Sum-of-two-numbers x
        Sum-of-two-numbers x
            Sum-of-two-numbers
                Sum-of-two-numbers x 2.
                Sum-of-two-numbers x 2....
