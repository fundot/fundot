# Fundot

Fundot Programming Language

## Language

* [中文](README.zh.md)
* English (shown below)

## Background

As someone who has always been interested in inventing a new programming language,
I started this project, Fundot, to make my idea come true.
Inspired by Lisp, Fundot is a functional programming language,
but it does not need parenthesis, "(" and ")", which is the biggest difference between Fundot and Lisp.
Instead, Fundot uses capital letters, "A" to "Z", and dot, ".", as we normally do in English,
to indicate the start and end of a function. More information can be found at [Fundot Documenation](https://fundot.readthedocs.io/en/latest/).

## Install

Clone or download this repository and compile the src files.
You can use the following command in terminals of Unix, macOS, Linux, and any other Unix-like systems under the repository.

    make
Fundot will be installed to /usr/local/bin by the above command. However, if you want to simply install it under the repository, then enter the following command.

    make build
After build, if you want to remove the object files generated, enter the following command.

    make clean

**Note: Any following code in this README so far is for Unix-like systems, but we will definitely support Windows in the future.**

## Usage

This program is a interpreter of Fundot programming language that contains the REPL (read-eval-print loop) mode and the file execution mode.

For REPL mode, simply enter fundot in the terminal.

    $ fundot
    Fun.
After displaying the information from Fundot, you can call functions and enjoy Fundot until you call Quit or Exit function.

    $ fundot
    Fun.
    >>> Add 1 2.
    3
    >>> Add Add 1 2. Add 1 2..
    6
    >>> Def Sum l.
            If Atom l. 0
            else Add First l. Sum Rest l.....
    defined
    >>> Def ls List 1 2 3 4 5..
    defined
    >>> Sum ls.
    15
    >>> Quit.
For file execution mode, access Fundot from terminal following an argument, the name of a .fundot file. For example, assume you have a file named test.fundot that contains the following content:

    Block
        Def ls List 1 2 3 4 5 6..
        Def Factorial n.
            If Equal n 1. 1
            else Mul n Factorial Sub n 1.....
        Print Factorial 5..
        Def Sum l.
            If Atom l. 0
            else Add First l. Sum Rest l.....
        Print Sum List 1 2 3 4 5...
        Def Product l.
            If Atom l. 1
            else Mul First l. Product Rest l.....
        Print Product ls..
        Def Square x.
            Mul x x..
        Print Square First Rest ls....
    test.fundot.
Then if you enter the following code in terminal under this repository, Fundot will output as below.

    $ fundot test.fundot
    Fun.
    120 
    15 
    720 
    4 
    test.fundot
**Note: So far, this interpreter has not been stable, and huge changes may occur in each new commit.**

## Contributing

Contributions are welcome.

## License

GPL-3.0 © Jiacheng Huang
