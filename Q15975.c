#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point Point;

uint64_t solve();
int32_t compare(const void*, const void*);
uint64_t abs_diff(uint32_t, uint32_t);

int main(void) {
    printf("%" PRIu64 "\n", solve());

    return 0;
}

typedef struct Point {
    uint32_t x, y;
} Point;

uint64_t solve() {
    uint32_t N, start = 0;
    uint64_t result = 0, min, right;
    scanf("%" SCNu32, &N);

    Point* points = malloc(sizeof(Point) * N);
    for (uint32_t i = 0; i < N; i++)
        scanf("%" SCNu32 "%" SCNu32, &points[i].x, &points[i].y);

    qsort(points, N, sizeof(Point), compare);

    for (uint32_t i = 1; i <= N; i++) {
        if (i == N || points[i].y != points[start].y) {
            for (uint32_t j = start; j < i; j++) {
                min = UINT64_MAX;

                if (j > start)
                    min = abs_diff(points[j].x, points[j - 1].x);

                if (j < i - 1) {
                    right = abs_diff(points[j].x, points[j + 1].x);
                    min = right < min ? right : min;
                }

                if (min != UINT64_MAX)
                    result += min;
            }

            start = i;
        }
    }

    free(points);

    return result;
}

int32_t compare(const void* a, const void* b) {
    Point *aa = (Point*)a, *bb = (Point*)b;

    return aa->y != bb->y ? aa->y - bb->y : aa->x - bb->x;
}

uint64_t abs_diff(uint32_t a, uint32_t b) {
    return a > b ? (uint64_t)(a - b) : (uint64_t)(b - a);
}