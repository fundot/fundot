# The Fundot Programming Language Specification

This is the official specification for Fundot programming language.

## READ ME FIRST

For convenience, we invent some notations, so a list of explanations is provided below:

    Notation     | Explanation
    [values]     | value_1 value_2 value_3 ... value_n
    <expression> | Function [arguments].

## Built-in Functions

    Def Function [arguments]. <body>.
Define a function named *Function* with a list of *arguments* as its arguments, and *body* as its body and return *defined*.

    Def variable value.
Define a variable named *variable* with *value* as its value and return *defined* and return *set*.

    Set variable value.
Set the value of an existing variable named *variable* to be *value*.

    Equal value_1 value_2.
Return *true* if *value_1* and *value_2* are equal and return *false* otherwise.

    Cond <predicate_1> <expression_1>
        <predicate_2> <expression_2>
        ... ...
        <predicate_n> <expression_n>
        else <expression_else>.
Return the value of the first expression whose predicate is *true*. The last line with *else* is not necessary.

    If <predicate> <expression_1>
        else <expression_2>.
Return the value of *expression_1* if the *predicate* is *true*, otherwise return the value of *expression_2*.

    Quote [arguments].
Return the list of *arguments* without evaluating.

    List [<expression>s].
Return the list of evaluated *expression*s.

    Atom [arguments].
Return true if *arguments* is an atom.

    CAR [arguments].
    First [arguments].
Both return the first argument of the list of *arguments*.

    CDR [arguments].
    Rest [arguments].
Both return the list of the rest of *arguments* except the first one.

    Cons element [arguments].
Return a list of *arguments* with *element* inserted at the first place.

    Eval <expression>.
Evaluate the evaluated *expression*.

    Import file_name.
Evaluate the file called file_name and return the evaluated value.

    Less value_1 value_2
Return *true* if *value_1* is less than *value_2* and return *false* otherwise.

    Greater value_1 value_2
Return *true* if *value_1* is greater than *value_2* and return *false* otherwise.

    Add value_1 value_2.
Return the sum of *value_1* and *value_2*.

    Sub value_1 value_2.
Return the difference of *value_1* and *value_2*.

    Mul value_1 value_2.
Return the product of *value_1* and *value_2*.

    Div value_1 value_2.
Return the quotient of *value_1* divided by *value_2*.

    Mod value_1 value_2.
Return the remainder of *value_1* divided by *value_2*.

    Block [<expression>s].
Execute all the *expression*s in the list and return the value returned by the last *expression*.

    Print value.
Print *value* on the terminal and return *null*.

    Quit.
    Exit.
Exit the program.
