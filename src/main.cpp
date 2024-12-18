#include "sieve.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: ./main.exe -n" << std::endl;
        return 1;
    }

    long long n = std::atoll(argv[1]);  
    std::cout << "n = " << n << '\n';

    return 0;
}
