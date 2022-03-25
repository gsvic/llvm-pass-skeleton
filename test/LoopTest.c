#include <stdio.h>

void a(int*);
void b(int*);
void c(int*);
void d(int);

int main(int argc, const char** argv) {
    int i = 5;
    long sum = 0;

    for (i=0; i<900000000; ++i) {
        long x = i * 2;
        sum += x;
    }

    printf("%ld\n", sum);
    return 0;
}
