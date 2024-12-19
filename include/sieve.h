#ifndef SIEVE_H
#define SIEVE_H

#include <iostream>
#include <vector>
#include <omp.h>
#include <math.h>
#include <climits>

void mark_primes(std::vector<bool> &is_prime, int i_limit);
long long sieve(long long n);

#endif
