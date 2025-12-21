#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define __uint64_t unsigned long long
#define rev "0.1"

bool isprime(const __uint64_t n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (__uint64_t i = 3; i*i<= n; i+=2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void welcome() {
    printf("Written by Dr. Lutz Bellmann, 2025");
    printf("\n");
}

void version() {
    printf("Prime for bash; Version %s\n", rev);
    welcome();
}

bool check_prime(const char* n) {
    const __uint64_t num = strtoll(n, NULL, 10);
    if (isprime(num)) {
        printf("%llu is prime\n", num);
        return true;
    }
    printf("%llu is not prime\n", num);
    return false;
}

void range_primes(const char* a, const char* b) {
    const __uint64_t start = strtoll(a, NULL, 10);
    const __uint64_t end = strtoll(b, NULL, 10);
    for (__uint64_t i = start; i <= end; i++) {
        if (isprime(i)) {
            printf("%llu ", i);
        }
    }
    printf("\n");
}

void list_primes() {
    for (__uint64_t i = 1; i <= pow(2, 64); i++) {
        if (isprime(i)) {
            printf("%llu ", i);
        }
    }
}

void help() {
    printf("Usage: prime [Options] ... [Number] ... [Directive]\n");
    printf("Options:\n");
    printf("  -h,   --help                Show help screen\n");
    printf("  -v,   --version             Show Version of this app\n");
    printf("  -p #, --prime               Show, if given number is a prime number\n");
    printf("  -s #, --start               Show all prime numbers from [start #]\n");
    printf("  -e #, --end                 Show all prime numbers up to [end #]\n");
    printf("  -l,   --list                List all prime numbers from 1 to 2^64-1\n");
    printf("Directives:\n");
    printf("  -S,   --Silent              Only output number(s)\n");
}

bool fatal_args(const int argc) {
    if (argc <= 1) {
        printf("Not enough arguments\n");
        help();
        return true;
    }
    if (argc > 5) {
        printf("Too many arguments\n");
        help();
        return true;
    }
    return false;
}

bool parse_args(int argc, char **argv) {
    if (fatal_args(argc)) return 1;
/*
    // Debug command options:
    printf("Number of arguments: %i\n", argc);
    for (int i=0;i<argc;i++) {
        printf("Argument %i: ",i);
        printf("%s\n", argv[i]);
    }
    // end of debug options
*/
    version();
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
        }
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        version();
        return 0;
    }
    if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--prime") == 0) {
        if (check_prime(argv[2])) return 1;
    }
    if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--start") == 0) {
        if (strcmp(argv[3], "-e") == 0 || strcmp(argv[1], "--end") == 0) {
            range_primes(argv[2], argv[4]);
        }
    }
    if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
        list_primes();
        return 1;
    }
    return false;
}



int main(int argc, char **argv) {
    if (parse_args(argc, argv)) return 1;
    return 0;
}
