# Contributing to Fundot

Thank you for your interest in Fundot! In this document, we are going to share with you some guidelines and rules for contributing.

## Contents

* [Code of Conduct](#code-of-conduct)
* [Where should I get started?](#where-should-i-get-started)
* [How can I contribute?](#how-can-i-contribute)
* [Coding Style](#coding-style)

## Code of Conduct

This project and everyone participating in it is governed by the Fundot Code of Conduct. By participating, you are expected to uphold this code. Please report unacceptable behavior to huangjiacheng0709@outlook.com.

## Where should I get started?

First of all, you should learn about the design philosophy of Fundot - "treating code as data". There is a discussion about this topic in the quick guide we provide. This feature is technically called homoiconicity, so if you want to know more about it, please google this term. You may also feel free to ask any questions in GitHub Discussions.

Second, be familiar with the project structure we are currently developing. So far, Fundot development is divided into roughly three parts:

* core
* shared objects
* scripts

Fundot core is the most important and necessary part, which rules how Fundot reads, evaluates, and prints. The files related are placed mainly in the `src` directory, and there are public headers placed in the `include` directory. In short, Fundot core deals with the logical part of Fundot.

On the contrary, shared objects are dynamically linked libraries that deal with problems that cannot be solved by pure Fundot. For example, we do not provide `quit` function to exit Fundot in the core part, and there is no other ways to implement it by simply writing Fundot scripts. Therefore, we must wrap the C++ `std::exit()` function as shared objects. The implementation for standard Fundot shared objects are placed in the `objects` directory.

Here is the interesting thing: Everybody is able to write shared objects easily. As you may see in the source files in the `objects` directory, you are able to implement a simple shared object in less than 50 lines. Shared objects are a great way to extend Fundot. Now you know why we separete this part from the core. We do so not only to divide and conquer, but also to give others an example how to write an external Fundot package with C++.

Scripts are simple. They are just text files with `.fun` suffix that contains pure Fundot code. The `init.fun` file in the root directory is a great example for this class. By default, Fundot runs the `init.fun` in the project root if there is one before everything else starts.

## How can I contribute?

To report a bug, use GitHub Issues and follow our ISSUE_TEMPLATE. Be sure to include the details about the specifc bugs you meet, and how to reproduce them.

For changes made in the core part, please think carefully about the neccessity, because we are trying to make the core as small as possible in order to better maintain it. Discuss it in GitHub Discussions before actually doing it.

For changes made in the shared objects part, think about the standard libraries of C/C++, Java, Python, and so on. Ask yourself: Is it better to make it a language standard or keep it as an external package? However, it is always encouraged to write packages for Fundot. You may send us your package website, and we will add it on a wiki page that lists available Fundot packages. Also, ask yourself: Can I implement the shared object in pure Fundot? Or is it highly related to efficiency problems?

After thinking clearly about the changes you want to make, please start a pull request and follow our PULL_REQUEST_TEMPLATE.

## Coding Style

When coding Fundot, please follow the guidelines we provide. So far, please follow this [C++ Style Guide](cpp_style.md).
