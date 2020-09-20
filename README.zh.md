# Fundot

Fundot 编程语言

## 语言

* 中文（如下）
* [English](README.md)

## 背景

作为一个一直对发明新的编程语言感兴趣的人，我开始了这个项目，Fundot，来让我的想法成真。Fundot 受 Lisp 的启发，是一种函数式编程语言，但它不需要括号，"("和")"，这是Fundot和Lisp之间最大的区别。相反，Fundot 使用大写字母"A"到"Z"，以及点，"."，就像我们平时用英语一样，来指示函数的开始和结束。更多信息可在 [Fundot Documentaion](https://fundot.readthedocs.io/en/latest/) 找到。

## 安装

### Linux, macOS, 以及其它 类unix 系统

从发布处下载或者直接从版本库克隆。在解压后的文件夹下输入make。

    make
通过上述命令，Fundot 将被安装到 /usr/local/bin。但是，如果您只想将其安装在解压后的文件夹下，请输入以下命令。

    make build
安装后，如果想要删除生成的object文件，请输入以下命令。

    make clean

### Windows

从发布处下载并将解压后的文件夹放入环境变量PATH中，以此来从任何位置访问。

**注意：此 README 中的以下任何代码都假设二进制文件已经被加入到PATH中。**

## 使用

此程序是 Fundot 编程语言的解释器，其中包含 REPL（read-eval-print loop）模式和文件执行模式。

对于 REPL 模式，只需在终端中输入 fundot。

    $ fundot
    Fun.
显示出 Fundot 的信息后，您可以调用函数并享受 Fundot，直到您调用Quit或Exit函数。

    $ fundot
    Fun.
    >>> Add 1 2.
    3
    >>> Add Add 1 2. Add 1 2..
    6
    >>> Def Sum l.
            If Atom l. 0
            else Add First l. Sum Rest l.....
    >>> Def ls [ 1 2 3 4 5 ].
    >>> Sum ls.
    15
    >>> Quit.
对于文件执行模式，从终端访问 Fundot，并带有参数，.fundot 文件的名称。例如，假设您有一个名为 test.fundot 的文件，其中包含以下内容：

    {
        Def ls [ 1 2 3 4 5 6 ].
        Def Factorial n.
            If Equal n 1. 1
            else Mul n Factorial Sub n 1.....
        Print Factorial 5..
        Def Sum l.
            If Atom l. 0
            else Add First l. Sum Rest l.....
        Print Sum [ 1 2 3 4 5 ]..
        Def Product l.
            If Atom l. 1
            else Mul First l. Product Rest l.....
        Print Product ls..
        Def Square x.
            Mul x x..
        Print Square First Rest ls....
    test.fundot
    }
那么，如果您在此版本库下的终端中输入以下代码，Fundot 将输出如下内容。

    $ fundot test.fundot
    Fun.
    120 
    15 
    720 
    4 
    test.fundot
**注意：到目前为止，此解析器不稳定，并且每个新提交中可能发生巨大的变化。**

## 贡献

欢迎贡献。

• 许可证

GPL-3.0 © 黄嘉成
