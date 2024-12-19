#include "sieve.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: ./main.exe -n" << std::endl;
        return 1;
    }

    long long n = std::atoll(argv[1]);  
    std::cout << "n = " << n << '\n';

    double start_time = omp_get_wtime();
    long long res = sieve(n);
    double end_time = omp_get_wtime();

    std::cout << "Number of primes = " << res << '\n';
    std::cout << "Time taken: " << (end_time - start_time) << " seconds" << std::endl;

    return 0;
}
