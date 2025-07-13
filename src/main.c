#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef long (*funcPtr) (long, long);

long gaypow(long ptr, long to) {
    long sum = 1;
    long i;
    for (i = 0; i < to; i++) {
        sum *= ptr;
    }
    return sum;
}

long plus(long ptr, long to) {
    return ptr + to;
}

long minus(long ptr, long to) {
    return ptr - to;
}

long multi(long ptr, long to) {
    return ptr * to;
}

long divide(long ptr, long to) {
    return ptr / to;
}

long module(long ptr, long to) {
    return ptr % to;
}

funcPtr funcs[] = {
    plus, minus, multi, divide, gaypow, module
};

int which(char what, char* from) {
    int i;
    for (i = 0; i < (int)strlen(from); i++) {
        if (from[i] == what)
            return i;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    long max = 64;
    char* fl = malloc(max);
    char* ops = "+-*/^%";
    int whch;
    long i;
    long sum = 0;
    long tmp = 0;
    long d = 0;
    if (argc <= 1) {
        printf("Enter formula (max %ld): ", max);
        fgets(fl, max, stdin);
    }
    else {
        max = 0;
        fl = malloc(max);
        for (i = 1; i < argc; i++) {
            max += strlen(argv[i]) + 2;
            fl = realloc(fl, max);
            fl = strcat(fl, argv[i]);
            fl = strcat(fl, " ");
        }
        fl = realloc(fl, max - 1);
    }
    for (i = 0; i < max; i++) {
        if (fl[i] != 0)
            whch = which(fl[i], ops) + 1;
        if (whch > 0) {
            if (d > 0) {
                tmp = funcs[d - 1](tmp, sum);
                sum = 0;
                d = 0;
            }
            else {
                tmp = sum;
                sum = 0;
            }
            d = whch;
        }
        else if (isdigit(fl[i])) {
            sum *= 10;
            sum += (fl[i] - '0');
        }
    }
    if (d > 0) {
        tmp = funcs[d - 1](tmp, sum);
        sum = 0;
    }
    else {
        tmp = sum;
        sum = 0;
    }
    if (tmp != 0 && sum == 0)
        sum = tmp;
    printf("Result: %ld\n", sum);
    free(fl);
    return 0;
}
