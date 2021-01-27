# Fundot Cheatsheet

This page provides quick references on how Fundot reads code as data.

## Contents

* [Comment](#comment)
* [Object](#object)
* [Reader](#reader)

## Comment

Everything after semicolons ';' are ignored, which can be used to comment Fundot code.

```Fundot
>>> (println "Hello, World!")  ; Hello, World!
```

You may notice that there is only one semicolon above, but you may use any number of semicolons as you wish. However, there are conventions to properly use semicolons to comment in some other languages. Here is an example in [Common Lisp Style Guide](https://lisp-lang.org/style-guide/#comment-hierarchy).

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
* [Getter - owner.index](#getter)
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

A getter is a owner-index pair that is used to get the value with the specific index out of the owner.

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

A Fundot list is a doubly linked list of objects. This is also the fundamental evaluation unit in Fundot. A list is default to be evaluated in Fundot.

```Fundot
(alpha "beta" 2.71828)
```

### Quote

A quote is a special form that contains one object after its invocation. The main effect of a quote is to prevent the contained object from being evaluated. For example, it is default for Fundot to evaluate a list by its front element, but placing a quote before that prevents it from being evaluated.

```Fundot
>>> (println 3.14)
3.14
null
>>> '(println 3.14)
(println 3.14)
```

## Reader

All the input in Fundot are done by `fundot::Reader`. Here is the strategy how it works. The words are boring, so we provide some code examples below.

1. The reader extracts an object from the input stream.
   1. The reader checks the first character. If the first character is a delimiter, such as '(', '[', '{', and so on, then the reader knows what type the upcoming data structure is.
   2. In a list, the only delimiter is ')', but in sets and vectors, commas ',' are used to separate elements. The elements in between delimiters are all stored in a list, and then will be parsed to see whether there are operators inside. A list keeps all the objects after parsing as its elements, while sets and vectors keep only the last element of the parsed object lists. The reader does so only for parsing operators, so please never write more than one top-level object between commas ',', otherwise all the objects except the last one are ignored.
   3. If the first charcter is a number, then the reader extracts a number.
   4. If all the above conditions are not met, then the reader extracts a symbol, and checks whether that is `true`, `false`or `null`. Then the reader returns any of them or simply a symbol.
2. The reader stores the object in a list as what happens when extracting elements in sets and vectors between commas ','.
3. The reader repeatedly does the first and the second step, until a newline is met. Here is a point: Not every newline stops the reader from reading, only the ones after a complete object stop.
4. As mentioned above, the list storing the objects is parsed to see whether there are operators. Then the last element of the parsed list is returned.

```Fundot
students : {        ; 'students' and ':' are stored in a list.
;   ^    ^ ^        ; The above newline does not stop reading,
  mike : {          ; because '{' tells the reader to extract a set,
    age : 19,       ; and the reader is still extracting an object.
    gender : male
  },                ; Now you see a comma ','. The elements in between
  tina : {          ; are 'mike', ':', and a set.
    age : 20,       ; They are then parsed and becomes a setter.
    gender : female ; This process is the same as below.
  }
}                   ; This newline stops reading, because it is
                    ; after a complete object.
;; Now, there are three elements in the top-level list in reader:
;; two symbols 'student' and ':', and a set.
;; The list is parsed.
;; Because there is a ':', which denotes a setter, the three elements
;; are combined as a setter, whose first element is 'students', and
;; whose second element is the set.
;; After parsing, there is only one object, the setter, in the list.
;; Therefore, the last (and also the first) element, the setter,
;; is returned.

students :          ; This newline stops reading, because the reader
{"some contents"}   ; is not extracting any objects.
;; Note: Never do this when coding! It causes undefined behaviors,
;; or even serious errors.

x : 0 y : 0         ; Now there are 6 elements in the reader list:
;; one 'x', two ':', one 'y', and two 0s.
;; They are parsed and becomes two setters.
;; However, the reader only cares about the last one in list.
;; Therefore, the first setter is ignored.
;; Now you may understand what I meant by "The reader does
;; so only for parsing operators, so please never write more
;; than one top-level object between commas ',',
;; otherwise all the objects except the last one are ignored.".
```

