# RISC-V ALE Exercise Book

This repository contains the Markdown files and images used to build the `ALE Exercise Book` used in the `MC404 - Computer Organization and Assembly Language` course at Universidade Estadual de Campinas (UNICAMP).

The exercise book contains a set of exercises to be solved using C or RISC-V Assembly language, and it serves as an additional learning resource to the textbook [An Introduction to Assembly Programming with RISC-V](https://riscv-programming.org/book.html).

The built book is available at https://riscv-programming.org/exercise-book.html

## Building the book

In order to generate the HTML files for the book Rust's [mdBook] is used, to install it from its [GitHub repository](https://github.com/rust-lang/mdBook).

At the root of this repository run

```bash
$ mdbook build
```

The resulting HTML files can be found in the `book` subdirectory.

### Authors

For further reference, below the authors list:

* João Seródio (@SerodioJ)
* Edson Borin (@eborin)
