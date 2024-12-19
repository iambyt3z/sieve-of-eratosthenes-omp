#include "sieve.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: ./main.exe -n" << std::endl;
        return 1;
    }

    long long n = std::atoll(argv[1]);  
    std::cout << "n = " << n << '\n';

    omp_set_num_threads(1);
    long long res = sieve(n);

    std::cout << "Number of primes = " << res << std::endl;

    return 0;
}
