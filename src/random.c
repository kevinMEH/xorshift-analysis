#include <stdio.h>
#include "random.h"

u64 xorshift(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 23;
    t ^= t >> 18;
    t ^= s ^ (s >> 5);
    state -> x[1] = t;
    return t + s;
}

u64 xorshiftAlt1(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 22; // Org: 23
    t ^= t >> 18;
    t ^= s ^ (s >> 5);
    state -> x[1] = t;
    return t + s;
}

u64 xorshiftAlt2(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 23;
    t ^= t >> 18;
    t ^= s ^ (s >> 7); // Org: 5
    state -> x[1] = t;
    return t + s;
}

u64 xorshiftAlt3(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 22; // 23
    t ^= t >> 17; // 18
    t ^= s ^ (s >> 4); // 5
    state -> x[1] = t;
    return t + s;
}

u64 xorshiftAlt4(ShiftState *state) {
    u64 t = state -> x[0];
    u64 s = state -> x[1];
    state -> x[0] = s;
    t ^= t << 22; // 23
    t ^= t >> 20; // 18
    t ^= s ^ (s >> 6); // 5
    state -> x[1] = t;
    return t + s;
}


void printBits(const size_t size, const void * const pointer) {
    unsigned char *b = (unsigned char*) pointer;
    unsigned char byte;
    for(int i = size - 1; i >= 0; i--) {
        for(int j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}