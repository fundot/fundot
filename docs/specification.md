# The Fundot Programming Language Specification

This is the official language specification for Fundot programming language.

## READ ME FIRST

For convenience, we invent some notations, so a list of explanations is provided below:

    Notation     | Explanation
    --------------------------------------------------
    [values]     | value_1 value_2 value_3 ... value_n
    <expression> | Function [arguments].

## Built-in Functions

```Fundot
Def Function [arguments]. <body>.
```
Define a *Function* of a list of *arguments* with *body*.

```Fundot
Def variable value.
```
Define a *variable* with *value*.

```Fundot
Let variable value.
```
Define a local *variable* with *value*.

```Fundot
Equal value_1 value_2.
```
Return *true* if *value_1* and *value_2* are equal and return *false* otherwise.

```Fundot
Cond <predicate_1> <expression_1>
    <predicate_2> <expression_2>
    ... ...
    <predicate_n> <expression_n>
    else <expression_else>.

If <predicate> <expression_1>
else if <predicate_2> <expression_2>
    ... ...
else if <predicate_n> <expression_n>
else <expression_else>.
```
Return the value of the first expression whose predicate is *true*. The last line with *else* is not necessary.

```Fundot
Quote [arguments].
```
Return *arguments* without evaluating.

```Fundot
List [<expression>s].
```
Return the list of evaluated *expression*s.

```Fundot
Atom [arguments].
```
Return true if *arguments* is an atom.

```Fundot
At vector index.
```

Return the element at position *index* in *vector*.

```Fundot
Push vector element.
```

Return a vector containing the elements in *vector* with *element* pushed back.

```Fundot
Pop vector.
```

Return a *vector* without its last element.

```Fundot
CAR [arguments].
First [arguments].
```
Both return the first argument of the list of *arguments*.

```Fundot
CDR [arguments].
Rest [arguments].
```
Both return the list of the rest of *arguments* except the first one.

```Fundot
Cons element [arguments].
```
Return a list of *arguments* with *element* inserted at the first place.

```Fundot
While <predicate> <expression>.
```
Evaluate *expression* if *predicate* is true.

```Fundot
Eval <expression>.
```
Evaluate the evaluated *expression*.

```Fundot
Return [arguments].
```

Return *arguments*.

```Fundot
Call file_name.
```
Evaluate the file called *file_name* and return the evaluated value.

```Fundot
Str@ string position.
```
Return the character of *string* at *position*.

```Fundot
Num= num_1 num_2
```
Return *true* if *num_1* is equal to *num_2* and return *false* otherwise.

```Fundot
Num<= num_1 num_2
```
Return *true* if *num_1* is less than or equal to *num_2* and return *false* otherwise.

```Fundot
Num>= num_1 num_2
```
Return *true* if *num_1* is greater than or equal to *num_2* and return *false* otherwise.

```Fundot
Num< num_1 num_2
```
Return *true* if *num_1* is less than *num_2* and return *false* otherwise.

```Fundot
Num> num_1 num_2
```
Return *true* if *num_1* is greater than *num_2* and return *false* otherwise.

```Fundot
Num+ num_1 num_2.
```
Return the sum of *num_1* and *num_2*.

```Fundot
Num- num_1 num_2.
```
Return the difference of *num_1* and *num_2*.

```Fundot
Num* num_1 num_2.
```
Return the product of *num_1* and *num_2*.

```Fundot
Num/ num_1 num_2.
```
Return the quotient of *num_1* divided by *num_2*.

```Fundot
Num% num_1 num_2.
```
Return the remainder of *num_1* divided by *num_2*.

```Fundot
Block [<expression>s].
```
Execute all the *expression*s in the list and return the value returned by the last *expression*.

```Fundot
File>> file_name.
```
Return the input from file named *file_name*.

```Fundot
File<< file_name value.
```
Output *value* to the file named *file_name* and return *null*.

```Fundot
Scan.
```
Return the input from user.

```Fundot
Print value.
```
Print *value* on the terminal and return *null*.

```Fundot
Quit.
Exit.
```
Exit the program.
