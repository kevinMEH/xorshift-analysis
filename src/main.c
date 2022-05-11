#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "random.h"

#define PATH "./test/"

int main() {
    FILE* report = fopen(PATH "report.txt", "w+");
    FILE* raw = fopen(PATH "raw.txt", "w+");

    ShiftState original;
    original.x[0] = 0b1101010000110100111010111101011000000111100010110110011101001100;
    original.x[1] = 0b0110110111110000011111110110000110011010111101111111101111010000
                    + (time(NULL) + 1) * (time(NULL) + 1) * time(NULL) * time(NULL);
    ShiftState state;

    memcpy(&state, &original, sizeof(state));
    simulate10k(&xorshift, &state, report, raw);
    
    fclose(report);
    fclose(raw);

    return 0;
}

void simulate10k(RandomFunction function, ShiftState* state, FILE* report, FILE* raw) {
    double numbers[10000];

    double totalDist = 0.0;
    double signedSquareDist = 0.0;

    u64 first = function(state);
    double last = (double) first / ((double) 0x8000000000000000u * 2.0);
    numbers[0] = last;
    
    for(int i = 1; i < 10000; i++) {
        u64 num = function(state);
        double normalized = (double) num / ((double) 0x8000000000000000u * 2.0);
        numbers[i] = normalized;
        
        totalDist += fabs(last - normalized);
        signedSquareDist += fabs(last - normalized) * (last - normalized);
        last = normalized;

        fprintf(raw, "%0.20lf\n", normalized);
    }
    
    double averageDist = totalDist / 9999;

    fprintf(report, "Average Distance Between Numbers: %lf\n", averageDist);
    fprintf(report, "Signed Square Distance Between Numbers: %lf\n", signedSquareDist);
}