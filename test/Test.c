#include <stdio.h>

void a(int*);
void b(int*);
void c(int*);
void d(int);

int main(int argc, const char** argv) {
    int called[3];

    a(called);

    return 0;
}

void a(int* called) {
    if (called[0] < 3) {
        called[0] += 1;

        printf("a\n");
        b(called);
    }
}

void b(int* called) {
    if (called[1] < 1) {
        called[1] += 1;

        printf("b\n");
        c(called);
    }
}
void c(int* called) {
    if (called[2] < 1) {
        called[2] += 1;

        printf("c\n");
        a(called);
        d(1);
    }
}

void d(int i) {
    printf("d: %d\n", i);
    if (i > 0 && i < 5) {
        d(i + 1);
    }
}