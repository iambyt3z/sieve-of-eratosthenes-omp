# Sieve of Eratosthenes using omp

## Description
This project implements the sieve of eratosthenes using omp library in C++ to use parallel processing. Through parallel processing, I was able to get an overall speedup on ~11 on 16 threads. The fastest implementation is done in the `src/sieve1.cpp` file.

## Installation

```bash
# Clone the repository
$ git clone https://github.com/iambyt3z/sieve-of-eratosthenes-omp.git

# Navigate to the project directory
$ cd your_project_name

# Build the project using make
$ make
$ ./build/main 10000000000
```