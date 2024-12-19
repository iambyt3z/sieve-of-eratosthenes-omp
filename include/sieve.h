#ifndef SIEVE_H
#define SIEVE_H

#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>

void mark_primes(std::vector<bool> &is_prime, int i_limit);
long long get_first_prime_multiple_after_n(long long n, long long prime);
long long sieve(long long n);

#endif
