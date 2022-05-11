#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "random.h"

typedef u64 (*RandomFunction)(ShiftState*);

int main();
void simulate10k(RandomFunction, ShiftState*, char* name);
int compareFloat(const void*, const void*);

#endif