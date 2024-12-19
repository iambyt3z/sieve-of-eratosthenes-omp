#include "sieve.h"

void 
mark_primes(std::vector<bool> &is_prime, int n)
{
    long long i_limit = static_cast<long long>(ceil(sqrt(n)));
    is_prime[0] = is_prime[1] = false;

    #pragma omp parallel for
    for(long long i=2; i <= i_limit; i++) {
        if(!is_prime[i])
            continue;

        for(long long j=i*i; j<=n; j+=i)
            is_prime[j] = false;
    }
}

long long 
get_first_prime_multiple_after_n(long long n, long long prime)
{
    long long first;

    if(prime * prime >= n) {
        first = prime * prime;
    } 
    
    else {
        if(n % prime == 0) {
            first = n;
        } else {
            first = n + (prime - n % prime);
        }
    }

    return first;
}

long long 
sieve
(long long n) {
    if(n<2) return 0LL;
    if(n==2) return 1LL;

    long long n_red = n - (n%2==0);
    long long n_sqrt = (long long) (ceil(sqrt(n)));
    long long i_min = 0;
    long long i_max = (n_red - 3LL)/2LL;
    long long i_bound = i_max + 1;
    long long res = 1LL;

    std::vector<bool> is_prime(n_sqrt+1, true);
    mark_primes(is_prime, n_sqrt); // Mark primes till sqrt(n)

    #pragma omp parallel // Mark primes from low_value to high_value
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        long long i_low_global = (tid * i_bound) / nthreads;
        long long i_high_global = ((tid + 1) * i_bound) / nthreads - 1;
        long long val_low_global = i_low_global * 2 + 3;
        long long val_high_global = i_high_global * 2 + 3;

        long long size = i_high_global - i_low_global + 1;
        std::vector<bool> is_prime_loc(size, true);

        for(long long curr_prime = 3LL; curr_prime * curr_prime <= val_high_global; curr_prime += 2)
        {
            if(!is_prime[curr_prime])
                continue;

            long long first = get_first_prime_multiple_after_n(val_low_global, curr_prime);

            for(long long num_global = first; num_global <= val_high_global; num_global += curr_prime)
            {
                if(num_global % 2 == 1)
                {
                    long long num_ind_global = (num_global - 3)/2;
                    long long num_ind_local = num_ind_global - i_low_global;
                    is_prime_loc[num_ind_local] = false;
                }
            }
        }

        long long res_loc = 0LL;
        for(int i=0; i<size; i++) 
        {
            res_loc += (long long) is_prime_loc[i];
        }

        #pragma omp atomic
        res += res_loc;
    }

    return res;
}
