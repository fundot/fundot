# Fundot

Fundot Programming Language

## Background

This project was initially my personl project called Jia, in which I want to realize my dream of creating a new programming language. After rewritting in C++, this project was renamed Fundot and placed into this organization. Recently inspired by LISP and JSON, I found a new way to combine code and data to make code-as-data programming much more readable.

## Install

### Linux, macOS, and any other Unix-like systems

Download the archive from release or simply clone from this repository. Enter make under the file you extracted.

    make
Fundot will be installed to /usr/local/bin by the above command. However, if you want to simply install it under the file extracted, then enter the following command.

    make build
After build, if you want to remove the object files generated, enter the following command.

    make clean

### Windows

Download the archive from release and add the extracted file to your PATH environment variable so that you can access it anywhere.

**Note: Any following code in this README assumes that the binary has already been added to PATH.**

## Usage

This program is a interpreter of Fundot programming language that contains the REPL (read-eval-print loop) mode and the file execution mode.

For REPL mode, simply enter fundot in the terminal.

    $ fundot
    Fundot> 
After displaying `Fundot>`, you can enter expressions and enjoy Fundot until you call exit function.

    $ fundot
    Fundot> x: 1
    x: 1
    Fundot> pi: 3.14
    pi: 3.14
    Fundot> (+ x pi)
    4.14
For file execution mode, access Fundot from terminal following a name or path of a .fd file. For example, assume you have a file named test.fd that contains the following content:

    [
        x: 0,
        (while (< x 10) [
            x: (+ x 1),
            (print x)
        ])
    ]
Then if you enter the following code in terminal under the directory that conatins test.fd, Fundot will output as below.

    $ fundot test.fd
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
**Note: So far, this interpreter has not been stable, and huge changes may occur in each new commit.**

## Contributing

Contributions are welcome.

## License

MIT License © Jiacheng Huang
