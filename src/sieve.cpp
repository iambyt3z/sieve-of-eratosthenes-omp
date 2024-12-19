#include "sieve.h"

void 
mark_primes(std::vector<bool> &is_prime, int n)
{
    long long i_limit = static_cast<long long>(ceil(sqrt(n)));

    #pragma omp parallel for
    for(long long i=2; i <= i_limit; i++) {
        if(!is_prime[i])
            continue;

        for(long long j=i*i; j<=n; j+=i)
            is_prime[j] = false;
    }
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
    is_prime[0] = is_prime[1] = false;
    long long loop_limit = static_cast<long long>(ceil(sqrt(n_sqrt)));
    mark_primes(is_prime, n_sqrt);

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

        long long first;
        long long curr_prime = 3LL;

        while(curr_prime * curr_prime <= val_high_global) {
            if(curr_prime * curr_prime >= val_low_global) {
                first = curr_prime * curr_prime;
            } 
            
            else {
                if(val_low_global % curr_prime == 0) {
                    first = val_low_global;
                } else {
                    first = val_low_global + (curr_prime - val_low_global % curr_prime);
                }
            }
            
            #pragma omp for
            for(long long num_global = first; num_global <= val_high_global; num_global += curr_prime)
            {
                if(num_global % 2 == 1)
                {
                    long long num_ind_global = (num_global - 3)/2;
                    long long num_ind_local = num_ind_global - i_low_global;
                    is_prime_loc[num_ind_local] = false;
                }
            }

            curr_prime++;
            while(!is_prime[curr_prime])
                curr_prime++;
        }

        long long res_loc = 0LL;
        
        #pragma omp for
        for(int i=0; i<size; i++) 
        {
            res_loc += (long long) is_prime_loc[i];
        }

        #pragma omp critical
        {
            res += res_loc;
        }
    }

    return res;
}
