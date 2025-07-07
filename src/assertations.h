#ifndef ASSERTATIONS_H
#define ASSERTATIONS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define fail exit(1)

void assert_equalsi(int a, int b);
void assert_equalsl(long a, long b);
void assert_equalsf(float a, float b);
void assert_equalsb(bool a, bool b);
void assert_equalsp(void* a, void* b);

#define assert_equals(X, Y) _Generic((X), \
    int: assert_equalsi, \
    long: assert_equalsl, \
    float: assert_equalsf, \
    bool: assert_equalsb, \
    default: assert_equalsp \
)(X, Y)


#endif
