# Fundot Beginner's Guide

This is a tutorial for Fundot beginners.

## Language

* [中文](guide.zh.md)
* English (shown below)

## Contents

1. [Introduction](#Introduction)
2. ["Hello, World!"](#"hello-world")
3. [Basic Building Blocks](#Basic Building Blocks)
4. [Syntax](#Syntax)
5. [Quote Symbol](#Quote Symbol)
6. [Function Definition](#Function Definition)
7. [Conditional Statement](#Conditional Statement)
8. [Equal Function](#Equal Function)
9. [Number](#Number)
10. [Atom Function](#Atom Function)
11. [Vector](#Vector)
12. [Block Function](#Block Function)
13. [Let Function](#Let Function)
14. [While Function](# While Function)
15. [Input && Output](#Input && Output)

## Introduction

Fundot is a functional programming language inspired by Lisp, whose goal is to provide a more readable solution for code-as-data programming.

## "Hello, World!"

Let's first write a program to print "Hello, World!" to get you familiar with Fundot programming language.

```Fundot
>>> Print "Hello, World!".
Hello, World!
```

The Print function we use prints its argument, a string. We can see from the above code that the syntax of Fundot is similar to Engish and thus is intuitive to many of us, which actually reflects the design philosophy of Fundot: Simplicity, Readability, and Intuitiveness. Now, let's learn Fundot in the rest of this tutorial.

## Basic Building Blocks

Fundot programs are made up of three basic building blocks:

* [Atom](#Atom)
* [String](#String)
* [Expression](#Expression)

### Atom

The smallest part of a Fundot program is an atom. Any string with lowercase capitals, which does not contain any "spaces" is an atom; an empty vector is also an atom. Here are some examples:

```Fundot
one-hundred
100
"hello"
Vect.
```

**Note:** "spaces" means whitespace, tab, newline, and any similar symbols that divide the string into parts.

### String

Fundot, similar to any other programming languages, has string, but we can discover from the above example that string like "hello" without any "spaces" is actually the same as an atom. However, sometimes there must be "spaces" inside the string, for example:

```Fundot
"Hello, World!"
```

Therefore, we need to define string as any characters with "spaces" inside and quoted by double quotes. For example:

```Fundot
" Hello, World! "
"My name is Mike."
"He says \"yes\"."
```

In the last example, we can see that we use '\' before double quotes. This is the escape character that avoids the misunderstanding of interpreter about when we want to use double quotes inside double quotes. If we want to express '\' in a string, we can use '\\\\'. For example:

```Fundot
>>> Print "He says \"yes\".".
He says "yes".
>>> Print " \\ \\ ".
 \ \ 
```

### Expression

Expression is the most fundamentai but most important syntax structure, since all functions are called through expressions. Any atom sequence that begins with a uppercase capital and ends with a dot is called an expression. An expression is actually a vector. For example:

```Fundot
x
Def x 1.
Num+ 1 1.
Quote x.
If true Print "true".
```

## Syntax

With the idea of simplicity and self consistency, the core syntax rules of fundot are very simple, which can be summarized in one sentence: in addition to the expressions contained in the quote function, fundot will execute all contents including function parameters and expression members from inside to outside. An example is as follows:

```Fundot
>>> Def x 1.
>>> Print x.
1
>>> Print Quote x..
x
>>> Def Quote x. 2.
>>> x
2
```

From the above code, we can realize the function of Quote function: to prevent the content inside from being executed. The Def function is used to define variables and functions, which will be described in detail later. What's more? When we first define x, we don't need to use the Quote function. This is because x is only x itself before it is defined, and the return value after it is executed is x itself. But after the first definition of x, if you want to redefine x, you must use the Quote function for x. Otherwise, before the def function is executed, the X in it will be executed, thus becoming 1, and the definition will become:

```Fundot
Def 1 2.
```

This is obviously not what we want in general.

## Quote Symbol

Because of the importance and particularity of quote function, Fundot provides two symbolic means to call Quote function: prefix single quote and suffix single quote.

### Prefix Single Quote

Prefix single quote makes the whole expression following enclosed by Quote function. For example:

```Fundot
'Def x 1.
```

is the same as

```Fundot
Quote Def x 1..
```

### Suffix Single Quote

Suffix Single Quote makes the inner part of the expression following enclosed by Quote function. For example:

```Fundot
Def' x 1.
```

is the same as

```Fundot
Def Quote x 1..
```

## Function Definition

In the above discussion, we used the built-in functions in the fundot language: Def, Quote, Print. But in many cases, the functions provided by fundot do not fully meet our needs. At this point, we need to define a function ourselves using Def function:

```Fundot
Def Function [arguments]. <body>.
```

This expression will be widely used in this guide, where the one in brackets is a sequence and the one in angle brackets is an expression, which is equivalent to:

```Fundot
Def Function argument_1 argument_2 ... argument_n. Body [arguments]..
```

Def function is used for both defining functions and defining variables. In fact, in Fundot, functions are almost the same as variables except for the ability to have parameters and use parameters. For example:

```Fundot
>>> Def x 1.
>>> x
1
>>> Def X. 1.
>>> X.
1
```

From the above code, we can see that if a function does not need any parameters, it is basically the same as a variable except for its expression. This also reflects Fundot's minimalism. Now let's define a function with parameters and use them:

```Fundot
>>> Def' Factorial n.
				If' Num= n 1. 1
				else Num* n Factorial Num- n 1.....
>>> Factorial 5.
120
```

We defined a factorial function and successfully output the factorial of 5: 120. Other built-in functions involved: Num=, Num*, Num- and If will be explained in the following chapters. Now you can simply think of them as: equality judgment, multiplication, subtraction and conditional statements. In short, the factorial function we defined, named Factorial, needs a parameter n when used. The function body returns 1 directly if n equals 1. Otherwise, it returns n * (n - 1)! and recurse until n equals 1. Although Fundot provides loops, it is more recommended to use recursion to define and use functions, because Fundot is designed as a functional language. The above functions can be expressed in mathematical language in the following forms:
$$
Factorial(n) =  
\begin{cases} 
	1 & n = 1 \\
	n * Factorial(n - 1) & otherwise
\end{cases}
$$

It is worth mentioning that the Fundot language does not rely on indentation and other formats for interpretation, but on language and symbols. The only effect of indentation is to make the code more beautiful. So the above function can also be written as:

```Fundot
Def' Factorial n. If' Num= n 1. 1 else Num* n Factorial Num- n 1.....
```

This way of writing in Fundot is exactly the same as the above way of writing. The only difference is that it is not convenient for programmers to read.

## Conditional Statement

### Cond Function

It stands to reason that the explanation of conditional statements should usually be placed after the variable definition and before the function definition. However, due to the special nature of the Fundot language, variables and functions are defined in the same way, so we have given priority to explain the Def function, and now we look back at the conditional statement. Readers in need can read this part and go back to browse the Factorial function defined before. The first function provided by the Fundot language for this is the Cond function:

```Fundot
Cond <predicate_1> <expression_1>
		<predicate_2> <expression_2>
		... ...
		<predicate_n> <expression_n>
		else <expression_else>.
```

The parameters of the Cond function are several predicates and corresponding expressions. The function is to execute the expression corresponding to the first predicate whose return value is true. Examples are as follows:

```Fundot
>>> Cond' false Num+ 1 1. false 1 true Num+ 2 2..
4
```

In this expression, the first predicate that returns true is true, so the expression immediately following it is executed, and the sum of two 2s is returned, which is 4. We can notice that there is a single quotation mark after Cond. Its function is to include all parameters of Cond using the Quote function (see [Quote symbol](#Quote symbol) for details), otherwise, before Cond executes, the `Num + 1 1.` and` Num + 2 2.` will be executed and become 2 and 4, although here, without single quotes, it will also return 4, but we usually want to judge first, and then execute, so under normal circumstances, Cond will be followed by a single quotation mark.


A keyword called else can be identified in the Cond statement. If none of the conditions before else is correct, the expression behind else is executed, but the else statement is not necessary. Examples are as follows:

```Fundot
>>> Cond false 0 false 1 false 2 else 3.
3
```

We can also see that because of the above parameters, no expression will be executed, so we do not need to add single quotes after Cond, but even if we add single quotes, the returned value is still the same, so in Fundot, if you cannot know whether to add such a quote, it is always a good habit to add suffix single quote after Cond.

### If Function

In order to cater to the vast number of programmers and intuition, we also provide If function as a conditional statement. We use it in the above factorial function. The specific usage is as follows:

```Fundot
If <predicate_1> <expression_1>
else if <predicate_2> <expression_2>
		... ...
else if <predicate_n> <expression_n>
else <expression_else>.
```

We can see that the If function is exactly the same as the Cond function, except that the else if keyword is added even more cumbersomely before the second to last predicates. Therefore, in Fundot, the function of the If function is to optimize the legibility of the conditional statement when there are only two cases, which are generally used as follows:

```Fundot
If <predicate> <expression>
else <expression_else>.
```

For example:

```Fundot
>>> Def x 1.
>>> If Equal x 0. 0
		else 1.
1
```

Writing this way does make the code more intuitive to a certain extent, but it is still recommended to use the Cond statement when multiple predicates are required.

## Equal Function

As one of Fundot's basic functions, the function of Equal is to determine whether its two arguments are equal:

```Fundot
Equal value_1 value_2.
```

If the two arguments are equal, it will return true, otherwise it will return false, such as:

```Fundot
>>> Def x 1.
>>> Def y 2.
>>> Equal x y.
false
>>> Def 'x 2.
>>> Equal x y.
true
```

At the beginning, we first defined the variables x and y, which are 1 and 2, respectively, so the return result of using the Equal function for them is false, but when we redefine x to 2 and use Equal again, the return value becomes True. However, it is worth mentioning that the Equal function judges that the form of the two after execution is not equal to the usual case, such as

```Fundot
>>> Equal 0 0.
true
>>> Equal 0 0.0.
false
>>> Num= 0 0.0.
true
```

Through the above code, we can find that 0 and 0 are indeed equal under the Equal function, but 0 and 0.0 are not. This is because although the two are equal in mathematics, they have different forms in Fundot. In cases, we need to use equality judgments in a targeted manner. For example, for two numbers, we usually use Num=.

## Number

In any programming language, the most processed data type is number, and the first data type supported in Fundot is number. In Fundot, due to the minimalist design concept, there is no specific distinction between digital types. But at present, the official interpreter provided by Fundot uses the double in C++ as the floating point of Fundot, and the long long in C++ as the integer of Fundot. Any number in the above range can be used normally. Here are some of the built-in functions related to numbers in Fundot:

* Num=
* Num>
* Num<
* Num>=
* Num<=
* Num+
* Num-
* Num*
* Num/
* Num%

Because the meaning and function of the above functions are very simple, they can be directly as the name implies. Here, we will not introduce them in detail, but directly give sample code:

```Fundot
>>> Def x 1.
>>> Def y 2.
>>> Num= x y.
false
>>> Num> x y.
false
>>> Num< x y.
true
>>> Num>= x y.
false
>>> Num<= x y.
true
>>> Num+ x y.
3
>>> Num- x y.
-1
>>> Num* x y.
2
>>> Num/ 1 2.
0.500000
>>> Num% 1 2.
1
```

## Atom Function

The Atom function is very simple in Fundot, but it is often used as an important predicate: the Atom function will judge the argument. If the argument is an atom, it returns true, otherwise it returns false. For example:

```Fundot
>>> Atom 1.
true
>>> Atom x.
true
>>> Atom 'Num+ 1 1..
false
>>> Atom [ 1 2 3 ].
false
>>> Atom [ ].
true
```

In the third expression, the prefix single quote is used in front of Num+. The function is to make the entire expression included in the Quote function, so the return value of Atom is false. If no single quote is added, the return result will be true, because before making a judgment, `Num + 1 1.` will be executed, which becomes atom 2. The content involved in the fourth and fifth expressions will be explained in detail in the content of the Vect function.

## Vector

Vectors can be said to be the most primitive data structure in Fundot, because each expression can be regarded as a vector, in which the words with initial capital letters start and the words with ending dots end. That's why, before saying that an empty vector is also an atom.

### Vect Function

The Vect function simply tells us that the content contained in the Vect function is a vector, and the start and end are marked. But its role can be reflected when processing atom sequences:

```Fundot
a b c d e
```

For such a string of atoms, we have no way of knowing their inclusion relationship. This is because atoms in Fundot do not have the ability to mark the start and end like expressions. At this time, the Vect function can play a role:

```Fundot
>>> Vect a b c d e.
[ a b c d e ]
>>> Vect Vect a b c. Vect d e..
[ [ a b c ] [ d e ] ]
```


We can see that this way we can clearly express the logical relationship of such a string of atoms, but this way of expression, for us humans, does not have an readable effect, but contrary to our design philosophy, So we introduced the Vect symbol.

### Vect Symbol

The role of the Vect symbol is exactly the same as the Vect function, which can be understood as a more readable alternative. The method of use is as follows:

```Fundot
>>> [ a b c d e ]
[ a b c d e ]
>>> [ [ a b c ] [ d e ] ]
[ [ a b c ] [ d e ] ]
```

In this way, our use of Vect functions becomes more intuitive and efficient.

### Vector Operational Functions

* At
* Push
* Pop

#### At Function

The meaning of the At function is very intuitive, which is to return the element at the specified position in the vector. The example is as follows:

```Fundot
>>> Def v [ 1 2 3 ].
>>> At v 1.
2
>>> Def v [ [ 1 2 ] 3 4 ].
>>> At v 0.
[ 1 2 ]
```


Since the element in the vector can be an atom or another vector, if the element at the specified position is a vector, this vector is returned.

#### Push Function

Push function returns a vector with the content of the first parameter vector and the second parameter added at the end. The example is as follows:

```Fundot
>>> Push [ 1 2 3 ] 4.
[ 1 2 3 4 ]
>>> Push [ [ 1 2 ] [ 3 4 ] ] [ 5 6 ].
[ [ 1 2 ] [ 3 4 ] [ 5 6 ] ] 
```

Since the element in the vector can be an atom or another vector, so if the second parameter element is a vector, the vector added at the end is also this vector.

#### Pop Function

Pop function returns a vector with the first parameter vector content but not including the end content.

```Fundot
>>> Pop [ 1 2 3 ].
[ 1 2 ]
>>> Pop [ [ 1 2 ] [ 3 4 ] ].
[ [ 1 2 ] ]
```

Since the element in the vector can be an atom or another vector, if the end element is a vector, the entire end vector is excluded.

### Lisp Axiomatic Functions

**Note: This chapter is not necessary to read**

Inspired by the Lisp language, Fundot also provides axiom functions in Lisp:

* CAR / First
* CDR / Rest
* Cons

#### CAR / First Function

CAR and First are substitutes for each other in Fundot, indicating the same function. The function is to return the first element in the parameter vector. An example is as follows:

```Fundot
>>> CAR [ 1 2 3 ].
1
>>> First [ 1 2 3 ].
1
>>> First [ [ 1 2 3 ] 4 5 ].
[ 1 2 3 ]
```

Since the element in the vector can be an atom or another vector, if the first element is a vector, this vector is returned.

#### CDR / Rest Function

CDR and Rest are substitutes for each other in Fundot, representing the same function. The function is to return a vector composed of elements other than the first element in the parameter vector. Examples are as follows:

```Fundot
>>> CDR [ 1 2 3 ].
[ 2 3 ]
>>> Rest [ 1 2 3 ].
[ 2 3 ]
>>> Rest [ [ 1 2 3 ] 4 5 ].
[ 4 5 ]
```

Combining the First function and Rest function, we can access all the elements in a vector, such as:

```Fundot
>>> First Rest [ 1 2 3 ]..
2
>>> First Rest Rest [ 1 2 3 ]...
3
>>> First First [ [ 1 2 3 ] 4 5 ]..
1
>>> First Rest First [ [ 1 2 3 ] 4 5 ]...
2
```

In the above code, we have accessed the second and third elements in [1 2 3], and the first and second in the first element in [[1 2 3] 4 5] Elements.

#### Cons Function

The function of the Cons function is to insert the first parameter into the first position in the second parameter vector. An example is as follows:

```Fundot
>>> Cons 1 [ 2 3 ].
[ 1 2 3 ]
>>> Cons [ 1 2 ] [ 3 4 ].
[ [ 1 2 ] 3 4 ]
```

Regardless of whether the first parameter is an atom or a vector, we can insert it.

So far, the seven axiom functions in the Lisp language have been explained, as follows:

* Quote
* Atom
* Equal
* Cond
* CAR
* CDR
* Cons

They are called the seven axiom functions because any other function can be composed of the above seven functions and related operations. If you are interested in this, you can learn about Lisp's seven axioms. But in fact, because in Lisp, the basic data type is list, and Fundot's basic data type is vector. If we use the above function forcibly, it will be counterproductive. What needs to be recognized is that the functions in the previous chapter can be used to construct the three functions in this chapter, so in Fundot, the seven most basic axiom functions are:

* Quote
* Atom
* Equal
* Cond
* At
* Push
* Pop

## Block Function

The functions we explained above are all executed on a single expression, but sometimes, we need a code block to execute the expression one by one. At this time, we can use the Block function. The execution of the Block function itself is also in the form of an expression, but it will return the last value. An example is as follows:

```Fundot
>>> Block Def x 1. Num+ x x..
2
```

In the above code, the Def function is executed first, so x in Num+ will be replaced by 1, and the function of the Block function is to return the last value, which is 2.

### Block Symbol

Considering the importance of the Block function in program development and its strong correlation with the While function to be introduced next, the Fundot language also provides alternative symbols for the Block function. The above program can be rewritten as:

```Fundot
>>> { Def x 1. Num+ x x. }
2
```

Simply put, replacing the operation symbol and corresponding period of the Block function to be used with front and back curly brackets can have the same effect.

## Let Function

The function of the Let function is similar to the Def function, but the Let function is to define a variable or function within a Block. It will lose its function after exceeding the scope of the Block. Examples are as follows:

```Fundot
>>> { Let x 1. Return x. }
1
>>> x
x
>>> { Let x 1. Num+ x x. }
2
```

The above code also uses the Return function. Here is a brief introduction to the reasons. In the current version of Fundot, due to the limitation of the interpretation process, the execution of an atom is parallel to other expressions, which leads to the direct output of x if x is used directly. The Return function here simply returns x, but it executes x, which makes it become 1. In other words, as long as the atomic form is not used directly, it can be executed after being defined.

## While Function

After explaining the above functions, in order to cater to the preferences of the majority of programmers, we also introduced loops in Fundot. The function of the While function is to continue to execute an expression in a loop when the predicate is true. The example is as follows:

```Fundot
>>> Def x 0.
>>> Def v [ ].
>>> While' Num< x 10. { Def 'v Push v x.. Def 'x Num+ x 1.. }.
[ 0 1 2 3 4 5 6 7 8 9 ]
```

The meaning of the above is very simple, we first define x as 0 and v as an empty vector, and then use the While function, when x is less than 10, loop: add x to v, and add 1 to x. So the result of the operation is a vector containing decimal single digits.

## Input && Output

### File>> Function

The File>> function means to input the content of the target file according to the atomic sequence and return a corresponding vector. Assuming that our working folder contains a file test.txt with contents 1 and 2, the example is as follows:

```Fundot
>>> File>> test.txt.
[1 2]
>>> Num+ At File>> test.txt. 0. At File>> test.txt. 1..
3
```

In the above, the first line returns a vector, while the second line adds the numbers in the returned vector in the same way.

### File<< Function

The File<< function means to output the target file in atomic sequence. Assuming that our working folder contains a file test.txt with empty content, the example is as follows:

```Fundot
>>> File<< test.txt 0.
>>> File<< test.txt 1.
>>> File<< test.txt 2.
>>> Def v File>> test.txt..
>>> v
[ 0 1 2 ]
```

The above code first enters three atoms into the empty text file test.txt using the File<< function, which are 0, 1, and 2, respectively. Then use the File>> function to define v as the file content, which is the last output vector.

### Print Function

The Print function has been involved at the beginning of this tutorial. Its meaning is to output certain content in the standard stream. The content can be an atom or a string. The example is as follows:

```Fundot
>>> Print x.
x
>>> Print "Hello, World!".
Hello, World!
>>> Def x 1.
>>> Print x.
>>> 1
```

After the above study, I believe that the above code should not need to be explained more.

### Scan Function

Scan function reads an atom from the standard input stream. The example is as follows:

```Fundot
>>> Def' Add. {
			Print "First:".
			Let first Scan..
			Print "Second:".
			Let second Scan..
			Print "Sum:".
			Print Num+ first second..
		}.
>>> Add. 
First: 
1
Second: 
2
Sum: 
3
```

Compared with the previous code, we use a lot of previous knowledge this time, so it seems relatively complicated, but the meaning is very intuitive: we define a function Add, the role is to allow the user to input two numbers, and finally output the sum .

## Eval Function

The function of the Eval function is very simple, it is to simply execute its parameter expression, the example is as follows:

```Fundot
>>> Def' two Num+ 1 1..
>>> Eval two.
2
```

Presumably, there is no need to explain too much.

## Call function

The function of the Call function is also very simple: read a .fundot file and execute it, but it is extremely important in Fundot, because the characteristic of Fundot is "code is data". In different files, .fundot files can be used as data The same is called seamlessly. Suppose we have a file test.fundot with the content `Num + 1 1.`, then the example is as follows:

```Fundot
>>>  Call test.fundot.
2
```

In many cases, we rely on the Call function to complete the mutual transfer of .fundot files.
