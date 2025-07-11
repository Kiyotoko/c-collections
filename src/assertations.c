#include <stdio.h>
#include "assertations.h"

#define CSI "\e["
#define ANSI_RESET CSI "0m"
#define ANSI_BOLD CSI "1m"
#define ANSI_DIM CSI "2m"
#define ANSI_RED CSI "91m"
#define ANSI_GREEN CSI "92m"

void fail_with(const char* str) {
    fprintf(stderr, "%s[error]%s %s%s\n", ANSI_RED ANSI_BOLD, ANSI_RESET ANSI_DIM, str, ANSI_RESET);
    fail;
}

void succeed_with(const char* str) {
    fprintf(stderr, "%s[success]%s %s%s\n", ANSI_GREEN ANSI_BOLD, ANSI_RESET ANSI_DIM, str, ANSI_RESET);
}

void assert_equalsi_with(int a, int b, const char* str) {
    if (a != b) {
        fail_with(str);
    }
}
void assert_equalsl_with(long a, long b, const char* str) {
    if (a != b) {
        fail_with(str);
    }
}
void assert_equalsf_with(float a, float b, const char* str) {
    if (a != b) {
        fail_with(str);
    }
}
void assert_equalsb_with(bool a, bool b, const char* str) {
    if (a != b) {
        fail_with(str);
    }
}
void assert_equalsp_with(void* a, void* b, const char* str) {
    if (a != b) {
        fail_with(str);
    }
}

void assert_equalsi(int a, int b) {
    if (a != b) {
        fprintf(stderr, "%s%sExpected %i, got %i%s\n",
            ANSI_RED, ANSI_BOLD, a, b, ANSI_RESET);
        fail;
    }
}
void assert_equalsl(long a, long b) {
    if (a != b) {
        fprintf(stderr, "%s%sExpected %li, got %li%s\n",
            ANSI_RED, ANSI_BOLD, a, b, ANSI_RESET);
        fail;
    }
}
void assert_equalsf(float a, float b) {
    if (a != b) {
        fprintf(stderr, "%s%sExpected %f, got %f%s\n",
            ANSI_RED, ANSI_BOLD, a, b, ANSI_RESET);
        fail;
    }
}
void assert_equalsb(bool a, bool b) {
    if (a != b) {
        fprintf(stderr, "%s%sExpected %s, got %s%s\n",
            ANSI_RED, ANSI_BOLD, a ? "true" : "false", b ? "true" : "false", ANSI_RESET);
        fail;
    }
}
void assert_equalsp(void* a, void* b) {
    if (a != b) {
        fprintf(stderr, "Expected %p, got %p\n", a, b);
        fail;
    }
}

void assert_true_with(bool v, const char* str) {
    if (!v) {
        fail_with(str);
    }
}
void assert_false_with(bool v, const char* str) {
    if (v) {
        fail_with(str);
    }
}

void assert_true(bool v) {
    if (!v) {
        fail_with("Expected true, got false");
    }
}
void assert_false(bool v) {
    if (v) {
        fail_with("Expected false, got true");
    }
}
