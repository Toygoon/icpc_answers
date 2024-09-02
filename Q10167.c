#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Point Point;
typedef struct Pair Pair;
typedef struct MSP MSP;

int64_t solve();
int compare(const void *, const void *);
MSP update(uint32_t, int32_t, uint32_t, uint32_t, uint32_t, MSP *);

int main(void) {
    printf("%" PRId64 "\n", solve());

    return 0;
}

typedef struct Point {
    uint32_t x, y, w;
} Point;

typedef struct Pair {
    uint32_t idx, value;
} Pair;

typedef struct MSP {
    int64_t sum, max_l, max_r, max_t;
} MSP;

int64_t solve() {
    uint32_t N, x, y, w, num, *size;
    scanf("%" SCNu32, &N);

    Pair *pair_x = (Pair *)malloc(sizeof(Pair) * N), *pair_y = (Pair *)malloc(sizeof(Pair) * N), **pairs = (Pair **)malloc(sizeof(Pair **) * N);
    Point *points = (Point *)malloc(sizeof(Point) * N);
    for (uint32_t i = 0; i < N; i++) {
        scanf("%" SCNu32 "%" SCNu32 "%" SCNu32, &x, &y, &w);

        pair_x[i].idx = i;
        pair_x[i].value = x;
        pair_y[i].idx = i;
        pair_y[i].value = y;
        points[i].w = w;

        pairs[i] = (Pair *)malloc(sizeof(Pair) * N);
    }

    qsort(pair_x, N, sizeof(Pair), compare);
    qsort(pair_y, N, sizeof(Pair), compare);

    num = 0;
    for (uint32_t i = 0; i < N; i++) {
        if (i != 0 && pair_x[i - 1].value != pair_x[i].value)
            num++;
        points[pair_x[i].idx].x = num;
    }

    num = 0;
    for (uint32_t i = 0; i < N; i++) {
        if (i != 0 && pair_y[i - 1].value != pair_y[i].value)
            num++;
        points[pair_y[i].idx].y = num;
    }

    size = (uint32_t *)calloc(N, sizeof(uint32_t));
    for (uint32_t i = 0; i < N; i++) {
        pairs[points[i].y][size[points[i].y]].idx = points[i].x;
        pairs[points[i].y][size[points[i].y]].value = points[i].w;
        size[points[i].y]++;
    }

    int64_t result = 0;
    MSP *msp;
    for (uint32_t i = 0; i < N; i++) {
        msp = (MSP *)calloc(4 * N, sizeof(MSP));
        for (uint32_t j = i; j < N; j++) {
            for (uint32_t k = 0; k < size[j]; k++) {
                uint32_t xx = pairs[j][k].idx, ww = pairs[j][k].value;
                update(xx, ww, 1, 0, N - 1, msp);
            }
            result = MAX(result, msp[1].max_t);
        }
        free(msp);
    }

    for (uint32_t i = 0; i < N; i++)
        free(pairs[i]);
    free(pair_x);
    free(pair_y);
    free(pairs);
    free(points);
    free(size);

    return result;
}

int compare(const void *a, const void *b) {
    return ((Pair *)a)->value - ((Pair *)b)->value;
}

MSP update(uint32_t idx, int32_t val, uint32_t node, uint32_t left, uint32_t right, MSP *msp) {
    if (idx < left || right < idx)
        return msp[node];

    if (left == right) {
        msp[node].sum += val;
        msp[node].max_l += val;
        msp[node].max_r += val;
        msp[node].max_t += val;

        return msp[node];
    }

    uint32_t mid = (left + right) / 2;
    MSP left_child = update(idx, val, node * 2, left, mid, msp), right_child = update(idx, val, node * 2 + 1, mid + 1, right, msp);

    msp[node].sum = left_child.sum + right_child.sum;
    msp[node].max_l = MAX(left_child.max_l, left_child.sum + right_child.max_l);
    msp[node].max_r = MAX(right_child.max_r, right_child.sum + left_child.max_r);
    msp[node].max_t = MAX(MAX(left_child.max_t, right_child.max_t), left_child.max_r + right_child.max_l);

    return msp[node];
}