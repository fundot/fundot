# Fundot

Fundot Programming Language

## Background

As someone who has always been interested in inventing a new programming language,
I started this project, Fundot, to make my idea come true.
Inspired by Lisp, Fundot is a functional programming language,
but it does not need parenthesis, "(" and ")", which is the biggest difference between Fundot and Lisp.
Instead, Fundot uses capital letters, "A" to "Z", and dot, ".", as we normally do in English,
to indicate the start and end of a function. More information can be found at [Fundot Documenation](https://fundot.readthedocs.io/en/latest/).

## Install

Clone or download this repository and compile the src files.
You can use the following command in terminals of Unix, macOS, Linux, and any other Unix-like systems under this repository.

    make
    make clean
**Note: Any following code in this README so far is for Unix-like systems, but we will definitely support Windows in the future.**

## Usage

This program is an underdeveloped parser of Fundot programming language that contains the REPL (read-eval-print Loop) mode and the file execution mode.

For REPL mode, simply access Fundot in the terminal under this repository.

    $ ./fundot
    Fun.
After displaying the information from Fundot, you can call one function a time, but you may call any functions inside that function, until you call the Exit or Quit function.

    $ ./fundot
    Fun.
    >>> Add 1 2.
    3
    >>> Add
            Add 1 2.
            Add 1 2..
    6
    >>> Def Sum-of-two-numbers a b. Add a b..
    defined
    >>> Def x 1.
    defined
    >>> Sum-of-two-numbers x
            Sum-of-two-numbers x
                Sum-of-two-numbers
                    Sum-of-two-numbers x 2.
                    Sum-of-two-numbers x 2....
    8
    >>> Quit.
For file execution mode, access Fundot from terminal following with an argument, the name of a .Fundot file. For example, assume you have a file named test.Fundot that contains the following content:

    Block
        Def Sum-of-two-numbers a b. Add a b..
        Def x 1.
        Sum-of-two-numbers x
            Sum-of-two-numbers x
                Sum-of-two-numbers
                    Sum-of-two-numbers x 2.
                    Sum-of-two-numbers x 2.....
Then if you enter the following code in terminal under this repository, an output 8 will be displayed after the information of Fundot.

    $ ./fundot test.fundot
    Fun.
    8
**Note: So far, this parser has not been stable, and huge changes may occur in each new commit.**

## Contributing

Contributions are welcome.

## License

GPL-3.0 © Jiacheng Huang
