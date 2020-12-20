# Fundot

Fundot is a  programming language that treats "code as data". Inspired by both Lisp and JSON, Fundot aims to provide homoiconicity, but with more readability and functionality.

## Installation

### Linux, macOS, and other Unix-like systems

Go to the directory where you want to build Fundot, and enter the following commands. Fundot will be built and then moved to `/usr/local/bin`, where local programs are normally installed. However, if you want to run Fundot only in the cloned directory, then please ignore the last line of commands.

    git clone https://github.com/Fundot/fundot.git
    cd fundot
    make
    sudo mv fundot /usr/local/bin
### Windows

Fundot should be able to run on Windows, but we have not tested the new versions yet. If you are interested, feel free to git clone the repository and compile the source. We will try to provide a new way to build Fundot by CMake so that Windows users are able to install Fundot easily.

**Note: Any following code in this README assumes that the binary has already been added to PATH.**

## Usage

This project is an evaluator of Fundot programming language, which contains the REPL (Read-Eval-Print Loop) mode and the file execution mode.

For REPL mode, simply enter `fundot` in the terminal.

    fundot
After displaying `>>> `, you may enjoy Fundot until you call `quit`.

```Fundot
>>> mike: {name: "Mike", age: 19}
{ name: "Mike", age: 19, }
>>> mike.age
19
>>> (defun square (x) (mul x x))
{ type: function, params: ( x ), body: ( mul x x ), }
>>> (square 4)
16
>>> mike.age: (add mike.age 16)
35
>>> (quit)
```
For file execution mode, enter `fundot` followed by the name of the source file. Suppose we have a source file named `example.fd` that contains the following code.

```Fundot
(defun square (x) (mul x x))

(defun abs (x)
  (if (comp< x 0)
    (sub 0 x)
    x))

(defun sqrt (x) [
  root: x,
  precision: 1e-9,
  (while (comp> (abs (sub x (square root))) precision)
    root: (div (add root (div x root)) 2)),
  root])

(print (sqrt 1))
(print (sqrt 2))
(print (sqrt 3))
(print (sqrt 4))
(print (sqrt 65536))
```
Then if we enter `fundot example.fd` in the terminal, we will get the output shown below.

    1
    1.41421
    1.73205
    2
    256
**Note: So far, Fundot has not been stable, and huge changes may occur in each new commit.**

## Contributing

Contributions are welcome. The guideline is coming soon.

## License

MIT License © Jiacheng Huang

