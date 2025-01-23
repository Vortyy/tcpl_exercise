# The C Programming Language Answers

Welcome to the repository for "tcpl_exercise" a.k.a "The C programming language Answers" — a comprehensive answers to exercises from the book The C programming language (B.R.KERNIGHAN && D.M.RITCHIE) 
This project aims to serve as complete annoted answers and reflexions for all developper that want to dive into C. 

I made these exercises with help, don't be affraid to use it, i want to share [ressources](ressources) that have been really helpful during this lecture, 
sometimes when you're stuck you're happy to understand or even compare your solution with other make you understand deeper the solution and maybe correct some mistakes.

## Getting Started

To get started with this repository it's easy :

1. Install a C compilers (*tested with gcc and clang*)
2. Clone this repository
```
git clone https://github.com/Vortyy/tcpl_exercise
cd tcpl_exercise/chapter_2
```
3. Compile and run the ex_1.c 
```
clang ex_1.c -o ex_1 -lm
./ex_1
```
4. don't hesitate to read and modify the code, this the goal of this repo !!!  

>[!TIP] 
> IF THEY ARE SOME REQUIREMENT THEY ARE WRITTEN INSIDE THE HEADER OF THE FILE\
> EXERCISES ARE NAMED LIKE THIS ex_i.c (answer for i) OR ex_i_j.c (answers for i to j) 

## Exercises Content

The book cover a large panels of topics by chapter about C, this is a brief the overview of each :

- [chapter_2](chapter_2) : Types, Operators and Expression (Precedence and Order of evaluation, etc.)
- [chapter_3](chapter_3) : Control Flow (recursivity, loops or goto etc.)
- [chapter_4](chapter_4) : Function and Program Structure (C Preprocessor, Scope, header files, etc.)
- [chapter_5](chapter_5) : Pointers and Arrays
- [chapter_6](chapter_6) : Data structure (Keyword struct, Typedef, Unions, etc.)
- [chapter_7](chapter_7) : IO (formatted input, output or argument lists, etc.)
- [chapter_8](chapter_8) : UNIX (syscall, low level IO, etc.)

## Ressources

**COMPILERS** : 
- [clang](https://clang.llvm.org/) 
- [GNU](https://gcc.gnu.org/)

**BOOKS** : 
- The C programming language (B.R.KERNIGHAN && D.M.RITCHIE) [9780131101630](https://en.wikipedia.org/wiki/Special:BookSources?isbn=9780131101630)
- The C answers book (CLOVIS L.TONDO && SCOTT E.GIMPEL) [9789332549739](https://en.wikipedia.org/wiki/Special:BookSources?isbn=9789332549739)
- man [command](https://en.wikipedia.org/wiki/Man_page) (don't neglect it you should use it, it gives really interesting intels)
- Lin Ke-Fong answers [github](https://github.com/anotherlin/tcpl)

**DEBUGGER** : (debugger save life and it's a greatime to start to learn how to use it !!!)
- [gdb](https://www.gnu.org/savannah-checkouts/gnu/gdb/index.html) 
- [ddd](https://www.gnu.org/software/ddd/)
