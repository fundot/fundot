# Quick Guide

Although Fundot is still under fast development, and huge changes may occur in each commit, there are still basic features that are quite stable. Therefore, it is time to write such a quick guide for others to understand the fundamental ideas and features of Fundot.

## Contents

* [Background](#background)
* [Cheatsheet](#cheatsheet)
* [Set](#set)
* [Setter](#setter)
* [Symbol](#symbol)
* [Getter](#getter)
* [Vector](#vector)
* [List](#list)
* [Quote](#quote)
* [Function](#function)
* [Special Form](#special-form)
* [Macro](#macro)
* [Conclusion](#conclusion)

## Background

### What is treating code as data?

Treating code as data is not a new idea. In fact, it is a very old one, becasue it is one of the features of the second-oldest high-level programming languge Lisp, which means it has a history of at least half a century. You may wonder what exactly "treating code as data" means? Now look at the following expression, what comes into your mind?

```Fundot
("apple" "banana" "orange")
```

Did you come up with "a list of fruits" or something similar? Yes, it represents a <u>data structure</u> that contains "apple", "banana", and "orange". Then what about the next expression?

```C
sqrt(2)
```

If you are already familiar with at least one of the other programming languages, you may come up with "a function call to calculate the square root of 2", which represents <u>code</u>. Now consider this one:

```Fundot
(sqrt 2)
```

If you come up with an idea of "a list of symbols that can be evaluated to calculate the square root of 2", then you are there. This kind of expression could be not only <u>code</u>, but also <u>data</u>. In this way, we are able to treat code exactly the same way as we treat data. Great, now you may catch the feel of "treating code as data". Here is an explanation for homoiconicity, the computer science terminology that describes treating code as data, from [Wikipedia](https://en.wikipedia.org/wiki/Homoiconicity).

> A language is **homoiconic** if a program written in it can be manipulated as data using the language, and thus the program's internal representation can be inferred just by reading the program itself.

Then you may be curious why this kind of programming language is not so popular. First, Lisp and many of its dialects are quite popular, if you don't compare them with the most popular programming languages, such as C++, Java, Python, and so on. Second, there is at least one reason that prevents them from being popular: the readability. To illustrate, I will show you a segment of Lisp code from the same [Wikipedia page](https://en.wikipedia.org/wiki/Homoiconicity).

```lisp
(setf expression  (list '* (list 'sin 1.1) (list 'cos 2.03)) )  
-> (* (SIN 1.1) (COS 2.03))    ; Lisp returns and prints the result
(third expression)    ; the third element of the expression
-> (COS 2.03)
(setf (first (third expression)) 'SIN)
; The expression is now (* (SIN 1.1) (SIN 2.03)).
```

You may now understand what I said about readability. It is really not easy to understand Lisp only from glance. The exprssions are kind of counter-intuitive. This is indeed the shortage of almost all kinds of homoiconic languages.

### What makes Fundot special?

As I mentioned above, homoiconicity is a special feature of a programming language, and most of the homoiconic languages have poor readability. However, inspired by both Lisp and JSON, Fundot is able to provide a much more human readable solution of homoiconic programming. Fundot provides more built-in data sturtcures, such as pairs, vectors, sets, and so on, in order to be more expressive, but still, everything in Fundot is data. So far, we have learnt about the basic ideas of treating code as data. Now, let's learn more about Fundot in details.

## [Cheatsheet](cheatsheet.md)

Before we dive into the world of Fundot, it is highly recommend to go through the [Cheatsheet](cheatsheet.md). After reading, you may have a complete view on how Fundot reads code as data. Most importrantly, you will learn about the basic building blocks of Fundot - the built-in data structures. If you feel boring about the last part of Cheatsheet, you may get back after you read everything else.

## Set

In Fundot, a set is an important data structure, because many objects, including macros and functions, are not primitive types, but just a set.

```Fundot
{"apple", "banana", "orange"}  ; A set of fruits.
```

A set contains a collection of unique elements. Together with setters, a key-value pair data sturcture that are only distinguished through their key parts, a set is able to be a map. In fact, most of the time, we are using a set just like a map in Fundot.

```Fundot
{
  name : "Mike",
  age : 19,
  gender : male
}
```

In order to manipulate a set, we are going to talk about setters and getters in details.

## Setter

As shown above, a setter is in the form of 

```Fundot
key : value
```

When a setter is evaluated, the `value` part is evaluated first, and then the setter is emplaced into the global scope. Therefore, setters are used to define global variables. Note that the `key` part of a setter is not evaluated.

```Fundot
>>> pi : 3.14
3.14
>>> pi
3.14
>>> pi_copy : pi
3.14
>>> pi_copy
3.14
```

## Symbol

Symbols have appeared many times in the above, and you may already know its functionality: when evaluated, get its corresponding value. If there is not a corresponding value, then a symbol is self-evaluated. This is very natural and intuitive, so I think a simple example is enough.

```Fundot
>>> pi
pi
>>> pi : 3.14
3.14
>>> pi
3.14
```

## Getter

A getter has the following form:

```Function
owner.index
```

When a getter is evaluated, both `owner` and `index` parts are evaluated first, and then it returns the element corresponding to the index in the owner.

```Fundot
>>> algorithm : {
      math : {pi : 3.14}
}
{math : {pi : 3.14}} 
>>> algorithm.'math
{pi : 3.14}
>>> algorithm.'math.'pi    ; You may also use algorithm.math.pi if
3.14                       ; you are sure.
```

You may recursively use a getter to get a deeper element in a data structure. Notice that I have added a quote ' in front of the indices. I did so in order to prevent the symbols from being evaluated. Quotes will be described in details later. If you are sure that you have never defined variables named 'math' and 'pi', you may get rid of the quote, but using a quote is always safer if the indices are not intended to be evaluated. In order to modify a deeper element in a data stucture, getters are able to be used together with a setter.

```Fundot
>>> algorithm : {
      math : {pi : 3.14}
}
{math : {pi : 3.14}}
>>> another_pi : 3.14159
3.14159
>>> algorithm.'math.'pi : another_pi
3.14159
>>> algorithm
{math : {pi : 3.14159}}
```

Moreover, setters and getters are not only for sets, but also for all kinds of built-in data types in Fundot. So far, you may use setters and getters with vectors and lists, and we will soon add support for pairs as well.

```Fundot
>>> fruits : ["apple", "banana", "orange"]
["apple", "banana", "orange"]
>>> fruits.(2)
"orange"
>>> food : {
      fruit_list : ("apple" "banana" "orange")
}
{fruit_list : ("apple" "banana" "orange")}
>>> food.'fruit_list.(0)
"apple"
```

If you have not gone throught [Cheatsheet](cheatsheet.md), you need to pay attention that commas ',' are necessary for vectors and sets, but should not be used in lists.

## Vector

Vectors are also very natural and intuitive, and they are default not to be evaluated, so you may feel free to use vector as you do in other programming languages. Here is a simple example:

```Fundot
fruits : ["apple", "banana", "orange"]
```

## List

In Fundot, a list is default to be evaluated. Therefore, lists are the tools that we use to apply special forms, macros, and functions, which will be explained in details in the following sections.

```Fundot
(apple banana orange)  ; They are symbols instead of strings this time.
```

First, the front element of a list is evaluated. In this case, `apple` is evaluated. If the object returned is a special from or a macro, then the rest of the list will not be evaluated and directly passed as arguments to that special form or macro. In all other cases, the remaining elements are evaluated in order. Then if the front object is a function, the rest are passed as arguments to that function. If none of the above happens, the evaluated list is returned. However, if there is only one element after evaluated, that element is returned, and if there is only an empty list after evaluated, then `null` is returned. In short, the strategy for evaluating a list is as follows:

1. Evaluate the front element.

2. * If the front is a special form or a macro, apply them directly,

   * else evaluate the rest of the list.

3. If the front is a function, apply it.

4. * Return`null` for an empty list,
   * the element for a list with only one element, or 
   * the evaluated list itself.

## Quote

However, sometimes you do not want a list, a setter, a getter, or something else to be evaluated. Then you need the quote. A quote stops Fundot from evaluating the quoted object, and returns that object directly. For example, if we want to simply create a shopping list, instead of calling a function or something, then we should do the following.

```Fundot
'("apple" "banana" "orange")         ;; Quote using '
```

In Fundot, a quote is also a data structure who contains only one object, but we do also provide a special form one to use.

```Fundot
(quote ("apple" "banana" "orange"))  ;; Quote using 'quote'
```

## Function

Functions are crucial in most programming languages, and they are much more important here in Fundot.

### What is a function?

We are not going to talk about the definitions of the terminology, but we are going to tell you what a function is like in Fundot.

```Fundot
{
  type : function,            ; Type specifier.
  params : [function_params], ; A vector of parameters.
  body : function_body        ; Function body to be evaluated,
}                             ; which can be any object.
```

Yes, a function in Fundot is just a set of some specific pairs. Precisely, a function set needs to have at least a type setter, a params setter, and a body setter. For example:

```Fundot
{
  type : function,
  params : [x],
  body : (if x < 0 (-x) x)
}
```

It is quite clear that this is a function that calculates the absolute value of x.

### How to apply a function?

We have learnt that a list is default to be evaluated, and the front element of a list is always the first to be evaluated. If the front element after evaluated is a function, then the rest of the list is evaluated and passed as the arguments of the function.

```Fundot
>>> ({type : function, params : [x], body : (if x < 0 (-x) x)} (-1))
1
```

A set is self-evaluated, which means it returns itself in evaluation, so the front elemtent is exactly a function. Then the rest of the list (which is just the second element in this case) is evaluated and passed as arguments. Therefore, the result is 1, since the absolute value of -1 is 1. In Fundot, we provide the lambda expression as another way to generate anonymous functions.

```Fundot
;; (lambda [params] body) generats a function set
>>> ((lambda [x] (if x < 0 (-x) x)) (-1))
1
```

### How to name a function?

Now you may complain that it is so boring to write the complet function set in order to apply it. Is there anyway to give an anonymous function a name? Yes! Because an anonymous function is just a specific set, we may use a setter to define a function.

```Fundot
abs : {
  type : function,
  params : [x],
  body : (if x < 0 (-x) x)
}

; or simply
abs : (lambda [x] (if x < 0 (-x) x))

(abs (-1))  ; Now you may use the name 'abs' to apply the function
```

Because 'abs' is first evaluated and becomes the function set, using the name is exactly the same as using an anonymous function.

Also, like most of the Lisp dialects, Fundot also provides a `defun` macro to generate a named function.

```Fundot
(defun abs [x] (if x < 0 (-x) x))  ;; Definition by 'defun'.
```

You may choose your favorite way to define a function, but keep in your mind to make your code clean and simple.

### May I change the function?

Yes, you may! Because functions are just sets in Fundot, you may modify or redefine a function in the same way you treat a set.

```Fundot
>>> some_fun : (lambda [x] (if x < 0 (-x) x))
{type : function, params : [x], body : (if x < 0 (-x) x)}
>>> some_fun.type                ; get type
function
>>> some_fun.params              ; get params
[x]
>>> some_fun.body                ; get body
(if x < 0 (-x) x)
>>> some_fun.body : (insert some_fun.body 3 'else)  ; insert 'else'
(if x < 0 (-x) else x)
>>> some_fun.body.(0) : 'cond    ; change the front to 'cond'
cond
>>> some_fun.body                ; get body
(cond x < 0 (-x) else else x)
>>> some_fun : (lambda [x, y] x * y)  ; redefinition
{type : function, params : [x, y], body : x * y}
>>> some_fun : "I am even not a function now."
```

The above changes are all trivial and not meaningful, but now you know the fact that a function can be manipulated in the same way you manipulate a set.

## Special Form

Special forms are different from functions by their evaluation rules. As I mentioned, a list is fully evaluated before applying a function, but this is not true for a special form. Each special form has its own evaluation rules. They are usually built-in parts of Fundot, and are never defined by users using Fundot. You may also treat the operators, such as setters, getters, adders, and so on, as special forms, but a special form is often called in a list just like a function. For example:

```Fundot
;; (if condition true? false?)
>>> (if 0 < 1 "Yes" "No")
"Yes"
```

`if` is a special form, which evaluates the condition first. If the condition is true, it evaluates and returns the element after the condition, "Yes" in this case, otherwise it evaluates and returns the other one, "No" in this case. Because different special forms have different evaluation rules, we are not going to provide detailed information for them in this quick guide, but we are going to write a separate documentation for them.

## Macro

Macros are also applied before the rest of a list is evaluated. They are important tools  to extend Fundot language. More importantly, macros are written in Fundot and can be easily user-defined. A macro is also a specific set, which is similar to a function.

```Fundot
{
  type : macro,               ; Type specifier.
  params : [macro_params],    ; A vector of parameters.
  body : macro_body           ; Macro body to be extended,
}                             ; which can be any object.
```

The macro system in Fundot is powerful, and we are able to use it to do amazing things. However, it is still not stable, so I will only provide an example code on how `defun` can be defined using macro system.

```Fundot
defun : {
  type : macro,
  params : [name, params, body],
  body : ('do
    name ': ('lambda params body))
}
```

For you to better understand how the macro system works, I will demonstrate the process step by step.

```Fundot
(defun abs [x] (if x < 0 (-x) x))  ; Fundot received a list.
   ^
  'defun'is evaluated and becomes
({body : ..., params : ..., type : macro} abs [x] (if x < 0 (-x) x))
                              ^  ^   ^
  Fundot knows that the front is of type macro
  and passes them directly as arguments.
('do name ': ('lambda params body)) ; This is the body of the macro
  After passing arguments and evaluating, it becomes
(do abs : (lambda [x] (if x < 0 (-x) x)))
  This is exactly the expansion of 'defun'.
  Note : 'do' is a function that returns the last element.
  Finally, the expression below is evaluated.
abs : (lambda [x] (if x < 0 (-x) x))
 ^
  Now abs has been created by using 'defun'.
```

In short, a macro is generally not used to calculate something, but used to generate a Fundot expression. In the above case,

```Fundot
(defun abs [x] (if x < 0 (-x) x))
```

generates

```Fundot
(do abs : (lambda [x] (if x < 0 (-x) x)))
```

Because the macro system is much more complicated and powerful than what I have shown, I will stop here in order not to make this quick guide a long one.

## Conclusion

So far, you have learnt the basics of Fundot. We may add more features to Fundot in the future, but what we mentioned in this guide are fundamental building blocks or even the design philosophy, so they should be quite stable. Thank you very much for going through this guide.

