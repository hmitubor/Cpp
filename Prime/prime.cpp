#include <iostream>
#include <bitset>
#include <math.h>
#include <omp.h>

bool is_Prime(const long val)
{
    long m = floor(sqrt(val));
    for (long i = 2; i <= m; i++) {
        if (0 == val%i) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    const long n = 10000000;
    std::bitset<n+1> arr;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (long i = 2; i < n; i++) {
        arr[i] = is_Prime(i);
    }

#ifdef _OPENMP
    std::cout << omp_get_num_procs() << std::endl;
#endif

    long sum = 0;
#ifdef _OPENMP
#pragma omp parallel for reduction (+:sum)
#endif
    for (long i = 2; i <= n; i++) {
        sum += arr[i] ? 1 : 0;
#if DEBUG
        std::cout << i << ": "
            << (arr[i] ? "true" : "false")
            << std::endl;
#endif
    }

    std::cout << "Prime = " << sum << std::endl;

    return 0;
}
