#include <vector>
#include <cmath>
#include <atomic>
#include <omp.h>

long long sieve0(long long n) 
{
    if (n < 2) return 0LL;
    if (n == 2) return 1LL;

    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    long long n_sqrt = static_cast<long long>(sqrt(n));
    long long res = 0LL;

    for (long long i = 2; i <= n_sqrt; i++) 
    {
        if (is_prime[i]) 
        {
            for (long long j = i * i; j <= n; j += i) 
            {
                is_prime[j] = false;
            }
        }
    }

    for (long long i = 0; i <= n; i++) 
    {
        res += is_prime[i];
    }

    return res;
}
