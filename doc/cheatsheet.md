# Fundot Cheatsheet

This page provides quick references on how Fundot reads code as data.

## Comments

Everything after semicolons ';' are ignored, which can be used to comment Fundot code.

```Fundot
>>> (print "Hello, World!")  ;; Hello, World!
```

You may notice that there are two semicolons above, but only one is necessary. You may use only one if you want, and you may even use any number of semicolons as you wish. However, there are conventions to properly use semicolons to comment in some other languages. Here is an example in [Common Lisp Style Guide](https://lisp-lang.org/style-guide/#comment-hierarchy).

>Comments that start with four semicolons, `;;;;`, should appear at the top of a file, explaining its purpose.
>
>Comments starting with three semicolons, `;;;`, should be used to separate regions of the code.
>
>Comments with two semicolons, `;;`, should describe regions of code within a function or some other top-level form, while single-semicolon comments, `;`, should just be short notes on a single line.

These tips are for Common Lisp, but it is recommended to also follow them in Fundot.

## Object

Everything in Fundot is an object, which can be roughly divided into three categories.

* [Atom](#atom)
* [Pair](#pair)
* [Container](#container)

## Atom

An atom is the smallest building block of Fundot that cannot be furthuer divided, which should be separated by whitespace.

* [String - "..."](#string)
* [Number](#number)
* [Boolean](#boolean)
* [Null](#null)
* [Symbol](#symbol)

### String

A string is a sequence of zero or more characters enclosed in double quotes.

```Fundot
"Hello, World!"
```

### Number

A number is an integer or a floating point number.

```Fundot
-5
3.14
```

### Boolean

A boolean represents the two truth values of logic, which can either be `true` or `false`.

```Fundot
true
false
```

### Null

A null is also treated as logical false in Fundot.

```Fundot
null
```

### Symbol

A symbol is a collection of contiguous characters that refers to something. If fundot does not find a match with any of the above atoms, then a symbol is invoked.

```Fundot
pi
```

## Pair

Because Fundot treats code as data, there is no syntax for operators. However, in order to improve readability, Fundot stores almost all commonly used binary operators in pair data sturctures.

* [Setter - key : value](#setter)
* [Getter - owner . key](#getter)
* [Adder](#adder)
* [Subtractor](#subtractor)
* [More Operators](#more-operators)

### Setter

A setter is a key-value pair that is used with a set to create a map. When evaluated, the right hand side of the setter will be evaluated, and then the setter will be emplaced in the global scope.

```Fundot
>>> pi
pi
>>> pi : 3.14
3.14
>>> pi
3.14
```

### Getter

A getter is a owner-key pair that is used to get the value with the specific key out of the owner.

```Fundot
>>> math : {pi : 3.14}
{pi : 3.14}
>>> math.pi
3.14
```

It is very convenient to use getters and setters together to access and modify values of owners.

```Fundot
>>> math.pi : 3.14159
3.14159
>>> math.pi
3.14159
```

### Adder

Adders are great examples for how Fundot treats operators as data structures. When an adder is evaluated, it returns the sum of its left hand side and right hand side.

```Fundot
>>> 1 + 1
2
```

### Subtractor

Similarly, when evaluated, a subtractor returns the difference of its left hand side and right hand side.

```Fundot
>>> 1 - 1
0
```

### More Operators

Fundot provides almost all necessary binary operators. Their functionalities, precedence, and associativities should be similar to what you have learnt in other languages. Here is a list of them.

```Fundot
binary_operators : {".", "*", "/", "%", "+", "-", "<<", ">>", "<", ">", "<=", ">=", "==", "!=", "&", "^", "|", "&&", "||", "=", ":"}
```

Fundot also provides the unary operators listed below. They are treated as data structures that stores a single object.

```Fundot
unary_operators : {"+", "-", "!", "~"}
```

So far, Fundot promises to recognize unary operators at the front of a list.

```Fundot
>>> (-1)  ;; '-' is at the front of the list.
(-1)
>>> -1    ;; Fundot reads objects as a list, so this is also okay.
(-1)
```



## Container

Containers store a collection of objects, which are invoked by their corresponding delimiters.

* [Set - { ... }](#set)
* [Vector - [ ... ]](#vector)
* [List - ( ... )](#list)
* [Quote - '](#quote)

### Set

A set stores a collection of unique elements.

```Fundot
{pi, 1.414, "Hello"}
```

You may notice that there is no map container in Fundot. You are right. We don't have a map, because we we provide the same functionality by combining sets and [setter pairs](#setter). After all, a map is just a a set of key-value pairs.

```Fundot
{
  pi: 3.14,
  greeting: "Hello"
}
```

### Vector

A vector is an ordered collection of objects.

```Fundot
[1, 2.71828, "Hello", 2]
```

### List

A Fundot list is a doubly linked list of objects. This is also the fundamental evaluation unit in Fundot. A list is default to be evaluated.

```Fundot
(alpha "beta" 2.71828)
```

### Quote

A quote is a special form that contains one object after its invocation. The main effect of a quote is to prevent the contained object from being evaluated. For example, it is default for Fundot to evaluate a list by its front element, but placing a quote before that prevents it from being evaluated.

```Fundot
>>> (print 3.14)
3.14
>>> '(print 3.14)
(print 3.14)
```
