#include <stdio.h>
#include <time.h>

#include "main.h"
#include "random.h"

int main() {
    ShiftState state;
    state.x[0] = 0b1101010000110100111010111101011000000111100010110110011101001100;
    state.x[1] = 0b0110110111110000011111110110000110011010111101111111101111010000
                    + (time(NULL) + 1) * (time(NULL) + 1) * time(NULL) * time(NULL);
    
    for(int i = 0; i < 1000; i++) {
        u64 num = xorshift(&state);
        printf("%0.5lf\n", num / (0x8000000000000000u * 2.0));
    }

    return 0;
}