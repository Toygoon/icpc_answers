#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const uint32_t MOD = 1000000007;

uint64_t solve();
void __mult(uint64_t[8][8], uint64_t[8][8]);
void __pow(uint64_t[8][8], uint32_t n);

int main(void) {
    printf("%" PRIu64 "\n", solve());

    return 0;
}

uint64_t solve() {
    uint32_t D;
    scanf("%d", &D);

    uint64_t F[8][8] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 1, 0}};

    __pow(F, D);
    return F[0][0];
}

void __mult(uint64_t F[8][8], uint64_t M[8][8]) {
    uint64_t result[8][8] = {0};
    for (uint32_t i = 0; i < 8; i++)
        for (uint32_t j = 0; j < 8; j++)
            for (uint32_t k = 0; k < 8; k++)
                result[i][j] = (result[i][j] + F[i][k] * M[k][j]) % MOD;

    for (uint32_t i = 0; i < 8; i++)
        for (uint32_t j = 0; j < 8; j++)
            F[i][j] = result[i][j];
}

void __pow(uint64_t F[8][8], uint32_t n) {
    if (n <= 1)
        return;

    uint64_t M[8][8] = {0};
    for (uint32_t i = 0; i < 8; i++)
        for (uint32_t j = 0; j < 8; j++)
            M[i][j] = F[i][j];

    __pow(F, n / 2);
    __mult(F, F);

    if (n % 2)
        __mult(F, M);
}