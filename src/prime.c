// prime.c
#include <math.h>

#include "prime.h"

int base = 50;

int next_prime(int base) {
    int x = base;
    while(is_prime(x) == 0) {
        x++;
    }
    return x;
}

int is_prime(int x) {
    int i = 3;
    while (i <= x) {
        if (x % i == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}