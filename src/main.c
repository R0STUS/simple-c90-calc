#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int gaypow(int ptr, int to) {
    int sum = 1;
    int i;
    for (i = 0; i < to; i++) {
        sum *= ptr;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    int max = 64;
    char* fl = malloc(max);
    int i;
    int sum = 0;
    int tmp = 0;
    int d = 0;
    if (argc <= 1) {
        printf("Enter formula (max %d): ", max);
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
        if (fl[i] == '+' || fl[i] == '-' || fl[i] == '*' || fl[i] == '/' || fl[i] == '^') {
            if (d > 0) {
                if (d == 1)
                    tmp += sum;
                else if (d == 2)
                    tmp -= sum;
                else if (d == 3)
                    tmp *= sum;
                else if (d == 4)
                    tmp /= sum;
                else
                    tmp = gaypow(tmp, sum);
                sum = 0;
                d = 0;
            }
            else {
                tmp = sum;
                sum = 0;
            }
            d = (fl[i] == '+') ? 1 : (fl[i] == '-') ? 2 : (fl[i] == '*') ? 3 : (fl[i] == '/') ? 4 : 5;
        }
        else if (isdigit(fl[i])) {
            sum *= 10;
            sum += (fl[i] - '0');
        }
    }
    if (d > 0) {
        if (d == 1)
            tmp += sum;
        else if (d == 2)
            tmp -= sum;
        else if (d == 3)
            tmp *= sum;
        else if (d == 4)
            tmp /= sum;
        else
            tmp = gaypow(tmp, sum);
        sum = 0;
    }
    else {
        tmp = sum;
        sum = 0;
    }
    if (tmp != 0 && sum == 0)
        sum = tmp;
    printf("Result: %d\n", sum);
    free(fl);
    return 0;
}
