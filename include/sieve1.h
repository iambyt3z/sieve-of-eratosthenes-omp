#ifndef SIEVE1_H
#define SIEVE1_H

#include <cmath>
#include <omp.h>
#include <vector>

void mark_primes(std::vector<bool> &is_prime, int i_limit);
long long get_first_prime_multiple_after_n(long long n, long long prime);
long long sieve1(long long n);

#endif
