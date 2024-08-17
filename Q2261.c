#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point Point;

static Point *points, *cands;

int32_t solve();
int32_t calc(int32_t, int32_t);
int compare_x(const void *, const void *);
int compare_y(const void *, const void *);
int32_t get_dist(Point, Point);
int32_t __min(int32_t, int32_t);

int main(void) {
    printf("%d\n", solve());

    return 0;
}

typedef struct Point {
    int32_t x, y;
} Point;

int32_t solve() {
    int32_t n, result;
    scanf("%d", &n);

    points = (Point *)malloc(sizeof(Point) * n);
    cands = (Point *)malloc(sizeof(Point) * n);

    for (int32_t i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    qsort(points, n, sizeof(Point), compare_x);
    result = calc(0, n - 1);

    free(points);
    free(cands);

    return result;
}

int32_t calc(int32_t l, int32_t r) {
    if (l == r)
        return __INT32_MAX__;

    if (r - l == 1)
        return get_dist(points[l], points[r]);

    int32_t m = (l + r) / 2, min_dist = __min(calc(l, m), calc(m + 1, r)), count = 0;
    for (int32_t i = l; i <= r; i++)
        if ((points[m].x - points[i].x) * (points[m].x - points[i].x) < min_dist)
            cands[count++] = points[i];

    qsort(cands, count, sizeof(Point), compare_y);
    for (int32_t i = 0; i < count - 1; i++) {
        for (int32_t j = i + 1; j < count && (cands[j].y - cands[i].y) * (cands[j].y - cands[i].y) < min_dist; j++) {
            min_dist = __min(min_dist, get_dist(cands[i], cands[j]));
        }
    }

    return min_dist;
}

int compare_x(const void *a, const void *b) {
    return ((Point *)a)->x - ((Point *)b)->x;
}

int compare_y(const void *a, const void *b) {
    return ((Point *)a)->y - ((Point *)b)->y;
}

int32_t get_dist(Point a, Point b) {
    int64_t dx = a.x - b.x, dy = a.y - b.y;
    return (int32_t)(dx * dx + dy * dy);
}

int32_t __min(int32_t a, int32_t b) {
    return a < b ? a : b;
}