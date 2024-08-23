#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue Queue;

int64_t solve();
Queue* create_queue(int32_t);
void free_queue(Queue*);
void push(Queue*, int32_t);
int32_t pop(Queue*);
int32_t top(Queue*);
int32_t parent(int32_t);
int32_t left(int32_t);
int32_t right(int32_t);
void swap(int32_t*, int32_t*);
void up(Queue*, int32_t);
void down(Queue*, int32_t);

int main(void) {
    printf("%" PRId64 "\n", solve());

    return 0;
}

typedef struct Queue {
    int32_t *heap, capacity, size;
} Queue;

int64_t solve() {
    int32_t N, A;
    scanf("%" SCNu32, &N);

    int64_t result = 0;
    Queue* q = create_queue(N);
    for (int32_t i = 0; i < N; ++i) {
        scanf("%" SCNu32, &A);
        A -= i;

        push(q, A);
        if (q->size > 0 && top(q) > A) {
            result += top(q) - A;

            pop(q);
            push(q, A);
        }
    }

    free_queue(q);
    return result;
}

Queue* create_queue(int32_t size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));

    q->heap = (int32_t*)malloc(size * sizeof(int32_t));
    q->capacity = size;
    q->size = 0;

    return q;
}

void free_queue(Queue* q) {
    free(q->heap);
    free(q);
}

void push(Queue* q, int32_t value) {
    if (q->size == q->capacity)
        return;

    q->heap[q->size] = value;
    up(q, q->size);

    q->size++;
}

int32_t pop(Queue* q) {
    if (q->size == 0)
        return -1;

    int32_t x = q->heap[0];
    q->heap[0] = q->heap[q->size - 1];
    q->size--;

    down(q, 0);

    return x;
}

int32_t top(Queue* q) {
    if (q->size == 0)
        return -1;

    return q->heap[0];
}

int32_t parent(int32_t i) {
    return (i - 1) / 2;
}

int32_t left(int32_t i) {
    return 2 * i + 1;
}

int32_t right(int32_t i) {
    return 2 * i + 2;
}

void swap(int32_t* a, int32_t* b) {
    int32_t t = *a;
    *a = *b;
    *b = t;
}

void up(Queue* q, int32_t i) {
    while (i > 0 && q->heap[parent(i)] < q->heap[i]) {
        swap(&q->heap[parent(i)], &q->heap[i]);
        i = parent(i);
    }
}

void down(Queue* q, int32_t i) {
    int32_t largest = i, l = left(i), r = right(i);

    if (l < q->size && q->heap[l] > q->heap[largest])
        largest = l;

    if (r < q->size && q->heap[r] > q->heap[largest])
        largest = r;

    if (largest != i) {
        swap(&q->heap[largest], &q->heap[i]);
        down(q, largest);
    }
}