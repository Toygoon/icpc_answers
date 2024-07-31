#include <stdio.h>
#include <stdlib.h>

typedef struct Robot Robot;

void solve();
double __fabs(double);
double __sqrt(double);
int compare(const void *, const void *);

typedef struct Robot {
    int i;
    double x, y, v, t;
} Robot;

int main(void) {
    solve();

    return 0;
}

void solve() {
    int N;
    scanf("%d", &N);

    Robot *r = (Robot *)malloc(sizeof(Robot) * N);
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf %lf", &r[i].x, &r[i].y, &r[i].v);
        r[i].i = i + 1;
        r[i].t = __sqrt(r[i].x * r[i].x + r[i].y * r[i].y) / r[i].v;
    }

    qsort(r, N, sizeof(Robot), compare);

    for (int i = 0; i < N; i++)
        printf("%d\n", r[i].i);

    free(r);
}

double __fabs(double x) {
    return x < 0 ? -x : x;
}

double __sqrt(double x) {
    if (x == 0 || x == 1)
        return x;

    double eps = 1e-6, y = x / 2, prev;

    do {
        prev = y;
        y = (y + x / y) / 2;
    } while (__fabs(y - prev) > eps);

    return y;
}

int compare(const void *a, const void *b) {
    Robot *aa = (Robot *)a, *bb = (Robot *)b;

    if (aa->t != bb->t)
        return (aa->t > bb->t) - (aa->t < bb->t);

    return aa->i - bb->i;
}