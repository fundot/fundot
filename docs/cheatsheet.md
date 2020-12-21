# Fundot Cheatsheet

This page provides quick references on how Fundot reads code as data.

## Object

Everything in Fundot is an object, which can be divided into three categories.

* Container
* Atom
* Pair

## Container

Containers store a collection of other objects, which are invoked by their corresponding delimiters.

* String - "..."
* List - ( ... )
* Set - { ... }
* Vector - [ ... ]
* Quote - '

### String

A string is a sequence of zero or more characters wrapped in double quotes.

```Fundot
"Hello, World!"
```

### Set

Sets store a collection of unique elements.

```Fundot
{pi, 1.414, "Hello"}
```

Commas are optional, so the following code also works. This is true not only in a set, but also in lists and vectors. In Fundot, a single comma is almost the same as a whitespace, but adding commas properly greatly enhances the readability of code.

```Fundot
{pi 1.414 "Hello"}
```

You may notice that there is no map container listed above. Don't worry, a map is just a set made up with key-value pairs. Fundot provides the same functionality by combining a set and a [setter pair](#Setter).

```Fundot
{
  pi: 3.14,
  greeting: "Hello"
}
```

### List

A Fundot list is a linked list of objects.

```Fundot
(alpha "beta" 2.71828)
```

As mentioned above, you may add commas in between objects, but it is a convention not to do that in a list, because lists are normally evaluated as a function call. It is weird to have a comma after the function name. As shown below, the second format seems much better.

```Fundot
(call, function)
(call function)
```

### Vector

A vector is an ordered collection of objects. The following two lines of code are equivalent, so feel free to pick up the one you like.

```Fundot
[1 2.71828 3.14 2]
[1, 2.71828, 3.14, 2]
```

### Quote

A quote is a special form that contains one object after its invocation. The main effect of quote is to prevent the contained object from being evaluated. For example, objects in a vector are default to be evaluated in sequence, and then return the last evaluation, so if you want to simply create a vector instead of evaluating it, please put a single quote in front of it.

```Fundot
>>> [1 2 3]
3
>>> '[1 2 3]
[ 1, 2, 3, ]
```

## Atom

An atom is the smallest building block of Fundot that cannot be furthuer divided, which should be separated by whitespace or comma. If Fundot does not receive any of the delimiters above, then an atom is invoked.

* Number
* Boolean
* Null
* Symbol

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

Also, a single comma that does not follow any of other objects, or more than one commas together are all treated as null.

```Fundot
>>> ,
null
>>> ,,,,,
null
>>> {1,, 2}
{ 2, null, 1, }
```

### Symbol

A symbol is a collection of contiguous characters that refers to something. If fundot does not find a match with any of the above atoms, then a symbol is invoked.

```Fundot
pi
```

## Pair

After the invocation of all of the above types, Fundot will try to recognize the next character immediately follows. If the next character immediately follows is not a space, nor any of the delimiters mentioned above, but a colon or a dot, then a pair will be formed.

* Setter - key: value
* Getter - key.value

### Setter

A setter is a key-value pair that is used to create a map together with a set. When evaluated, a setter inserts the pair into the scope.

```Fundot
>>> pi
pi
>>> pi: 3.14
3.14
>>> pi
3.14
```

### Getter

A getter is also a key-value pair, but is used to get the value with the specific key out of the scope.

```Fundot
>>> math: {pi: 3.14}
{ pi: 3.14, }
>>> math.pi
3.14
```

