#include <stdbool.h>
#include <stdio.h>

void solve();
int gcd(int, int);
double sqrt(double);
double dist(int *, int *);

int main(void) {
    solve();

    return 0;
}

void solve() {
    int s[2], e[2], d[2], result[2], cur[2], g, t = 0;
    scanf("%d %d", &s[0], &s[1]);
    scanf("%d %d %d %d", &e[0], &e[1], &d[0], &d[1]);

    g = gcd(d[0], d[1]);
    for (int i = 0; i < 2; i++) {
        d[i] /= g;
        result[i] = e[i];
    }

    double min_dist = dist(e, s), cur_dist;

    while (true) {
        t++;
        for (int i = 0; i < 2; i++)
            cur[i] = e[i] + d[i] * t;

        cur_dist = dist(cur, s);

        if (cur_dist < min_dist) {
            min_dist = cur_dist;
            result[0] = cur[0];
            result[1] = cur[1];
        } else {
            break;
        }
    }

    printf("%d %d\n", result[0], result[1]);
}

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

double sqrt(double x) {
    if (x == 0 || x == 1)
        return x;

    double g = x / 2, eps = 1e-7, next = -1;
    for (next = (g + x / g) / 2; g - next >= eps || next - g >= eps; g = next);

    return next;
}

double dist(int *cur, int *s) {
    int xx = cur[0] - s[0], yy = cur[1] - s[1];

    return sqrt(xx * xx + yy * yy);
}