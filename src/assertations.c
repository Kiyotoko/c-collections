#include "assertations.h"

void assert_equalsi(int a, int b) {
    if (a != b) {
        fprintf(stderr, "Expected %i, got %i\n", a, b);
        fail;
    }
}
void assert_equalsl(long a, long b) {
    if (a != b) {
        fprintf(stderr, "Expected %i, got %i\n", a, b);
        fail;
    }
}
void assert_equalsf(float a, float b) {
    if (a != b) {
        fprintf(stderr, "Expected %f, got %f\n", a, b);
        fail;
    }
}
void assert_equalsb(bool a, bool b) {
    if (a != b) {
        fprintf(stderr, "Expected %i, got %i\n", a, b);
        fail;
    }
}
void assert_equalsp(void* a, void* b) {
    if (a != b) {
        fprintf(stderr, "Expected %p, got %p\n", a, b);
        fail;
    }
}
