# The Fundot Programming Language Specification

This is the official language specification for Fundot programming language.

## READ ME FIRST

For convenience, we invent some notations, so a list of explanations is provided below:

    Notation     | Explanation
    --------------------------------------------------
    [values]     | value_1 value_2 value_3 ... value_n
    <expression> | Function [arguments].

## Built-in Functions

    Def Function [arguments]. <body>.
Define a *Function* of a list of *arguments* with *body*.

    Def variable value.
Define a *variable* with *value*.

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
Return the value of *expression_1* if *predicate* is *true*, otherwise return the value of *expression_2*.

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

    While <predicate> <expression>.
Evaluate *expression* if *predicate* is true.

    Eval <expression>.
Evaluate the evaluated *expression*.

    Call file_name.
Evaluate the file called *file_name* and return the evaluated value.

    Str@ string position.
Return the character of *string* at *position*.

    Num= num_1 num_2
Return *true* if *num_1* is equal to *num_2* and return *false* otherwise.

    Num<= num_1 num_2
Return *true* if *num_1* is less than or equal to *num_2* and return *false* otherwise.

    Num>= num_1 num_2
Return *true* if *num_1* is greater than or equal to *num_2* and return *false* otherwise.

    Num< num_1 num_2
Return *true* if *num_1* is less than *num_2* and return *false* otherwise.

    Num> num_1 num_2
Return *true* if *num_1* is greater than *num_2* and return *false* otherwise.

    Num+ num_1 num_2.
Return the sum of *num_1* and *num_2*.

    Num- num_1 num_2.
Return the difference of *num_1* and *num_2*.

    Num* num_1 num_2.
Return the product of *num_1* and *num_2*.

    Num/ num_1 num_2.
Return the quotient of *num_1* divided by *num_2*.

    Num% num_1 num_2.
Return the remainder of *num_1* divided by *num_2*.

    Block [<expression>s].
Execute all the *expression*s in the list and return the value returned by the last *expression*.

    File>> file_name.
Return the input from file named *file_name*.

    File<< file_name value.
Output *value* to the file named *file_name* and return *null*.

    Scan.
Return the input from user.

    Print value.
Print *value* on the terminal and return *null*.

    Quit.
    Exit.
Exit the program.
