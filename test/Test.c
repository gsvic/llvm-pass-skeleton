#include <stdio.h>

void a(int*);
void b(int*);
void c(int*);
void d(int);

int main(int argc, const char** argv) {
    int i = 5;

    if (i < 2) {
        printf("False\n");
    }
    else {
        printf("True\n");
    }

    if (i > 2) {
        printf("True\n");
    }
    else {
        printf("False\n");
    }

    if (i > 100) {
        printf("True\n");
    }
    else {
        printf("False\n");
    }

    return 0;
}
