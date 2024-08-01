#include <stdio.h>

int main(void) {
    int N;
    scanf("%d", &N);
    getchar();

    while (N--) {
        char c;

        while (c = getchar(), c != '\n') {
            if ('A' <= c && c <= 'Z')
                c += 32;

            printf("%c", c);
        }
        printf("\n");
    }

    return 0;
}