#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern int32_t double_input(int32_t input);

int main() {
    volatile int input = 4;
    volatile int output;

    char test[10];
    memset( test, 0, sizeof(test) );

    float a = 1.0;
    float b = 999999.9999;

    float c;

    c = a*b;

    while( 1 ) {
        output = double_input(input);

        for(int i=0; i < 1000000; i++ ) {
            asm("NOP");
        }
    }
    // printf("%d * 2 = %d\n", input, output);
    return 0;
}
