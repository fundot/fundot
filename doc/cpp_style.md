# C++ Style Guide

This guide is mainly based on [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines). It is very recommended to read them even though you don't want to code Fundot interpreter, because this is a great way to learn C++ better and improve your coding skills.

Note: This guide is not mature and under development.

## General Rules

When coding Fundot interpreter, you should treat this document with the highest priority, which means whenever you meet a conflict, please follow this guide. [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) is a set of comprehensive guidelines for using C++ well, and [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) is more about styles of coding. Whenever there is a conflict between them, please follow the former one.

There is no real guide of truth in C++ programming, and what we have provided is just one of the many possibilities, but we still need to follow this guide to better maintain our project. Therefore, if you are dealing with something not mentioned in all of those documents, just remember to keep everything clean and simple, and then you will be fine.

## Naming

* In general, choose meaningful and understandable names.
* Do not abbreviate a name unless the abbreviation is widely used.

### File Names

File names should be all lowercase with underscore '_' as the word separator.

### Type Names

Type names should be in upper camel case (stylized as CamelCase).

### Variable Names

* Variable names should be all lowercase with underscores '_' as the word separator.
* Private data members should have trailing underscores.

### Constant Names

Constant names should be in upper camel case (stylized as CamelCase).

### Enumerator Names

Constant names should be in upper camel case (stylized as CamelCase).

### Function Names

Function names should be in lower camel case (stylized as camelCase).

### Macro Names

It is highly not recommended to define a macro in modern C++, except header guards, but if you do, macro names should be all upper case with underscores '_' as the word separator.

### Exceptions to Naming Rules

If you are naming something that is analogous to an existing C or C++ entity then you can follow the existing naming convention scheme.

## Formatting

To help you format code correctly, we've created a [clang-format](.clang-format) file.

### Line Length

Each line of text in your code should be at most 80 characters long.

### Spaces vs. Tabs

Use only spaces, and indent 4 spaces at a time.

### Layout

Use K&R-derived layout. In your editor, this style is often called “Stroustrup”. Please read [NL.17: Use K&R-derived layout](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl17-use-kr-derived-layout) of [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) to see an example of this style.

## References

* [C++ Core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

