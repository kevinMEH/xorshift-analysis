#ifndef RANDOM_H
#define RANDOM_H

#include "util.h"

typedef struct ShiftState {
    u64 x[2];
} ShiftState;

u64 xorshift(ShiftState*);
u64 xorshiftAlt1(ShiftState*);
u64 xorshiftAlt2(ShiftState*);
u64 xorshiftAlt3(ShiftState*);
u64 xorshiftAlt4(ShiftState*);
void printBits(const size_t, const void * const);

#endif