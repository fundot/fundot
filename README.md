# Jia

Jia Programming Language

## Background

As someone who has always been interested in inventing a new programming language,
I started this project, Jia, to make my idea come true.
Inspired by Lisp, Jia is a functional programming language,
but it does not need parenthesis, "(" and ")", which is the biggest difference between Jia and Lisp.
Instead, Jia uses capital letters, "A" to "Z", and dot, ".", as we normally do in English,
to indicate the start and end of a function. A JIADOC.md file is also included in this repository, which describes the language features of Jia in details.

## Install

Clone or download this repository and compile the src files.
You can use the following command in terminals of Unix, macOS, Linux, and any other Unix-like systems under this repository.

    make
**Note: Any following code in this README so far is for Unix-like systems, but we will definitely support Windows in the future.**

## Usage

This program is an underdeveloped parser of Jia programming language that contains the REPL (Read, Evaluate, and Print Loop) mode and the file execution mode.

For REPL mode, simply access Jia in the terminal under this repository.

    $ ./jia
    Jia is here.
After displaying the information from Jia, you can call one function a time, but you may call any functions inside that function, until you call the Exit function.

    $ ./jia
    Jia is here.
    Add 1 2.
    3
    Add
        Add 1 2.
        Add 1 2..
    6
    Def Sum-of-two-numbers a b. Add a b..
    Def x 1.
    Sum-of-two-numbers x
        Sum-of-two-numbers x
            Sum-of-two-numbers
                Sum-of-two-numbers x 2.
                Sum-of-two-numbers x 2....
    8
    Exit.
For file execution mode, access Jia from terminal following with an argument, the name of a .jia file. For example, assume you have a file named test.jia that contains the following content:

    Block
        Def Sum-of-two-numbers a b. Add a b..
        Def x 1.
        Sum-of-two-numbers x
            Sum-of-two-numbers x
                Sum-of-two-numbers
                    Sum-of-two-numbers x 2.
                    Sum-of-two-numbers x 2.....
Then if you enter the following code in terminal under this repository, an output 8 will be displayed after the information of Jia.

    $ ./jia test.jia
    Jia is here.
    8
**Note: So far, this parser has not become stable, and huge changes may occur for each new commit.**

## Contributing

Contributions are welcome.

## License

GPL-3.0 © Jiacheng Huang
