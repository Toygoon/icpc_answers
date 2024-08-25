#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;

static const size_t MAX_P = 5133, MAX_PRIME = 50001;
static int32_t *prime, P;

int64_t solve();
Queue *create_queue(int32_t);
void free_queue(Queue *);
void push(Queue *, int64_t, int32_t, int32_t);
Node pop(Queue *);
bool is_empty(Queue *);
void check(int64_t, int64_t *, bool *);

int main(void) {
    printf("%" PRIu64 "\n", solve());

    return 0;
}

typedef struct Node {
    int64_t n;
    int32_t idx, sign;
} Node;

typedef struct Queue {
    Node *data;
    int32_t capacity, size;
} Queue;

int64_t solve() {
    int64_t K, k, result = 1ULL << 31;
    scanf("%" SCNu64, &K);

    P = 0;
    prime = (int32_t *)malloc(sizeof(int32_t) * MAX_P);
    bool *visited = (bool *)calloc(MAX_PRIME, sizeof(bool)), is_sq_mult;
    for (int32_t i = 2; i < MAX_PRIME; i++) {
        if (!visited[i]) {
            prime[P++] = i;

            if (i < 317)
                for (int32_t j = i * i; j < MAX_PRIME; j += i)
                    visited[j] = true;
        }
    }

    int32_t bit = 30; 
    while (bit >= 0) {
        check(result, &k, &is_sq_mult);

        if (k < K)
            result += 1ULL << bit;
        else if (k > K || (k == K && is_sq_mult))
            result -= 1ULL << bit;
        else
            break;

        bit--;
    }

    free(visited);
    free(prime);

    return result;
}

Queue *create_queue(int32_t capacity) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (Node *)calloc(capacity, sizeof(Node));
    q->capacity = capacity;
    q->size = 0;

    return q;
}

void free_queue(Queue *q) {
    free(q->data);
    free(q);
}

void push(Queue *q, int64_t n, int32_t idx, int32_t sign) {
    if (q->capacity == q->size) {
        q->capacity *= 2;
        q->data = (Node *)realloc(q->data, sizeof(Node) * q->capacity);
    }

    q->data[q->size++] = (Node){n, idx, sign};
}

Node pop(Queue *q) {
    return q->data[--q->size];
}

bool is_empty(Queue *q) {
    return q->size == 0;
}

void check(int64_t n, int64_t *k, bool *is_sq_mult) {
    Queue *q = create_queue(100);
    push(q, 1, -1, 1);

    *k = 0;
    *is_sq_mult = false;

    while (!is_empty(q)) {
        Node node = pop(q);

        for (int32_t i = node.idx + 1; i < P; i++) {
            int64_t new_n = node.n * (int64_t)prime[i] * prime[i];

            if (new_n > n)
                break;

            *k += n / new_n * node.sign;
            *is_sq_mult |= (n % new_n == 0);

            push(q, new_n, i, -node.sign);
        }
    }

    free_queue(q);
    *k = n - *k;
}