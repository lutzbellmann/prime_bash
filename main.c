#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define __uint64_t unsigned long long
#define rev "0.51"

/**
 * Checks if a number is prime using trial division.
 * 
 * @param n The 64-bit unsigned integer to check.
 * @return true if prime, false otherwise.
 */
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

/**
 * Prints the author information.
 */
void welcome() {
    printf("Written by Dr. Lutz Bellmann, 2025");
    printf("\n");
}

/**
 * Prints the program version and author info.
 */
void version() {
    printf("Prime for bash; Version %s\n", rev);
    welcome();
}

/**
 * Converts a string to a number and prints whether it is prime.
 * 
 * @param n String input from command line.
 * @return true if the number is prime.
 */
bool check_prime(const char* n) {
    const __uint64_t num = strtoll(n, NULL, 10);
    if (isprime(num)) {
        printf("%llu is prime\n", num);
        return true;
    }
    printf("%llu is not prime\n", num);
    return false;
}

/**
 * Calculates and prints all primes between two values.
 * 
 * @param a Start of the range (string).
 * @param b End of the range (string).
 */
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

/**
 * Custom power function for unsigned 64-bit integers.
 * 
 * @param base The base number.
 * @param exp The exponent.
 * @return The result of base^exp.
 */

/*
__uint64_t spow(int base, int exp)
{
    __uint64_t result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}
*/
/**
 * Exhaustive list of all primes up to 2^64-1.
 * @note This function is extremely slow for large ranges.
 * TODO: use a Sieve of Erathosthenes for calculating ranges of primes!
 */
void list_primes() {
    /**
     *  used UINT64_MAX instead of spow for now
    */
//    __uint64_t top = spow(2, 64);
    __uint64_t top = UINT64_MAX;
    for (__uint64_t i = 1; i < top; i++) {
        if (isprime(i)) {
            printf("%llu ", i);
        }
    }
}

/**
 * Displays help instructions and command-line options.
 */
void help() {
    printf("Usage: prime [Options] ... [Number] ... [Directive]\n");
    printf("Options:\n");
    printf("  -h,   --help                Show help screen\n");
    printf("  -v,   --version             Show Version of this app\n");
    printf("  -p #, --prime               Show, if given number is a prime number\n");
    printf("  -s #, --start               Show all prime numbers from [start #]\n");
    printf("  -e #, --end                 Show all prime numbers up to [end #]\n");
    printf("  -l,   --list                List all prime numbers from 1 to 2^64-1; will take long!\n");
    printf("Directives:\n");
    printf("  -S,   --Silent              Only output number(s)\n");
}

/**
 * Validates that the number of arguments is within acceptable bounds.
 * 
 * @param argc Number of arguments.
 * @return true if arguments are invalid.
 */
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

/**
 * Orchestrates the command-line argument parsing and program execution.
 * 
 * @param argc Argument count.
 * @param argv Argument array.
 * @return true if an error occurred or immediate exit is required.
 */
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
    
    // Handle help request
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
        }
    
    // Handle version request
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        version();
        return 0;
    }

    // Handle single prime check
    if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--prime") == 0) {
        if (check_prime(argv[2])) return 1;
    }

    // Handle range check (e.g., -s 10 -e 100)
    if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--start") == 0) {
        if (strcmp(argv[3], "-e") == 0 || strcmp(argv[3], "--end") == 0) {
            range_primes(argv[2], argv[4]);
        }
    }

    // Handle full list request
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
