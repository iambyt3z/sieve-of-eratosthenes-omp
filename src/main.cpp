#include "sieve0.h"
#include "sieve1.h"
#include "sieve2.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: ./main.exe -n" << std::endl;
        return 1;
    }

    long long n = std::atoll(argv[1]);  
    std::cout << "n = " << n << "\n\n";

    std::vector<int> thread_cnts = {1, 2, 4, 8, 16};
    int runs_cnt = 10;

    for(int tc: thread_cnts)
    {
        std::cout << "Thread count = " << tc << "\n\n";
        omp_set_num_threads(tc);

        double sieve0_total_time = 0;
        double sieve1_total_time = 0;
        double sieve2_total_time = 0;
        long long res;

        std::cout << "Executing sieve0\n";

        for(int i=0; i<runs_cnt; i++)
        {
            double start_time = omp_get_wtime();
            res = sieve0(n);
            double end_time = omp_get_wtime();

            sieve0_total_time += (end_time - start_time);
        }

        double sieve0_avg_time = sieve0_total_time / runs_cnt;

        std::cout << "Number of primes = " << res << '\n';
        std::cout << "Average execution time = " << sieve0_avg_time << "sec \n\n";

        std::cout << "Executing sieve1\n";

        for(int i=0; i<runs_cnt; i++)
        {
            double start_time = omp_get_wtime();
            res = sieve1(n);
            double end_time = omp_get_wtime();

            sieve1_total_time += (end_time - start_time);
        }

        double sieve1_avg_time = sieve1_total_time / runs_cnt;

        std::cout << "Number of primes = " << res << '\n';
        std::cout << "Average execution time = " << sieve1_avg_time << "sec \n\n";

        std::cout << "Executing sieve2\n";

        for(int i=0; i<runs_cnt; i++)
        {
            double start_time = omp_get_wtime();
            res = sieve2(n);
            double end_time = omp_get_wtime();

            sieve2_total_time += (end_time - start_time);
        }

        double sieve2_avg_time = sieve2_total_time / runs_cnt;

        std::cout << "Number of primes = " << res << '\n';
        std::cout << "Average execution time = " << sieve2_avg_time << "sec \n\n";

        double speedup_12 = sieve2_avg_time / sieve1_avg_time;
        double speedup_10 = sieve0_avg_time / sieve1_avg_time;
        std::cout << "Speedup of 1 w.r.t. 0 = " << speedup_10 << "\n";
        std::cout << "Speedup of 1 w.r.t. 2 = " << speedup_12 << "\n\n";
    }

    return 0;
}
