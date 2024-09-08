#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t solve();

int main(void) {
    printf("%" PRIu64 "\n", solve());

    return 0;
}

uint64_t solve() {
    uint32_t N, M, L, R, *colors, dist = 0;
    scanf("%" SCNu32 "%" SCNu32, &N, &M);

    colors = (uint32_t *)calloc(N + 1, sizeof(uint32_t));
    bool *x = (bool *)calloc(N + 1, sizeof(bool));

    for (uint32_t i = 1; i <= M; i++) {
        scanf("%" SCNu32 "%" SCNu32, &L, &R);

        for (uint32_t j = L; j <= R; j++)
            colors[j] = i;
    }

    for (uint32_t i = 1; i <= N; i++) {
        if (colors[i] && !x[colors[i]]) {
            x[colors[i]] = true;
            dist++;
        }
    }

    free(colors);
    free(x);

    return 1ULL << dist;
}