#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "random.h"

typedef u64 (*RandomFunction)(ShiftState*);
typedef struct Result {
    double chiScore;
    double totalSquaredDiffDist;
    double averageDist;
    double signedSquareDist;
} Result;

int main();
void simulate10k(RandomFunction, ShiftState*, Result*, char*);
void writeReport(FILE* , Result*, char*);
int compareFloat(const void*, const void*);

#endif