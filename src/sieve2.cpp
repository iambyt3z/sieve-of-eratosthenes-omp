#include "sieve2.h"

long long 
sieve2(long long n) 
{
    if (n < 2) return 0LL;
    if (n == 2) return 1LL;

    long long n_red = n - (n % 2 == 0);
    long long n_sqrt = static_cast<long long>(sqrt(n));
    long long i_max = (n_red - 3LL) / 2LL;

    long long high_ind = (n - 3LL) / 2LL;
    long long size = high_ind + 1;

    std::vector<char> is_prime(size, true);
    long long res = 1LL;

    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for(long long i=3; i<=n_sqrt; i+=2)
        {
            long long ind_i = (i - 3LL) / 2LL;

            if(is_prime[ind_i] == 1)
            {
                for(long long j=i*i; j<=n; j+=2*i)
                {
                    long long ind_j = (j - 3LL) / 2LL;
                    is_prime[ind_j] = 0;
                }
            }
        }

        long long local_res = 0LL;

        #pragma omp for schedule(dynamic)
        for(long long i=0; i<size; i++)
        {
            local_res += is_prime[i];
        }

        #pragma omp atomic
        res += local_res;
    }

    return res;
}
