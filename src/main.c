#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define max 64

int gaypow(int ptr, int to) {
    int sum = 1;
    int i;
    for (i = 0; i < to; i++) {
        sum *= ptr;
    }
    return sum;
}

int main() {
    char* fl = malloc(max);
    int i;
    int sum = 0;
    int tmp = 0;
    int d = 0;
    printf("Enter formula (max %d): ", max);
    fgets(fl, max, stdin);
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
