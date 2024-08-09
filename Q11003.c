#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Deque Deque;

void solve();
Deque *create_deque();
void free_deque(Deque *);
void push(Deque *, bool, int, int);
int pop(Deque *, bool);
bool is_empty(Deque *);

int main(void) {
    solve();

    return 0;
}

typedef struct Node {
    int idx, value;
    Node *next, *prev;
} Node;

typedef struct Deque {
    int size;
    Node *head, *tail;
} Deque;

void solve() {
    int N, L, *A;
    scanf("%d %d", &N, &L);

    A = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    Deque *d = create_deque();
    for (int i = 0; i < N; i++) {
        if (!is_empty(d) && d->head->idx < i - L + 1)
            pop(d, true);

        while (!is_empty(d) && d->tail->value > A[i])
            pop(d, false);

        push(d, false, i, A[i]);
        printf("%d ", d->head->value);
    }
    printf("\n");

    free(A);
    free_deque(d);
}

Deque *create_deque() {
    Deque *d = (Deque *)calloc(1, sizeof(Deque));
    
    return d;
}

void free_deque(Deque *d) {
    while (d->head != NULL)
        pop(d, true);

    free(d);
}

void push(Deque *d, bool is_front, int idx, int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->idx = idx;
    n->value = value;

    if (is_front) {
        n->next = d->head;
        n->prev = NULL;

        if (d->head)
            d->head->prev = n;
        else
            d->tail = n;

        d->head = n;
    } else {
        n->next = NULL;
        n->prev = d->tail;

        if (d->tail)
            d->tail->next = n;
        else
            d->head = n;

        d->tail = n;
    }
}

int pop(Deque *d, bool is_front) {
    if (is_empty(d))
        return -1;

    Node *tmp = is_front ? d->head : d->tail;
    int value = tmp->value;

    if (is_front) {
        d->head = d->head->next;

        if (d->head)
            d->head->prev = NULL;
        else
            d->tail = NULL;
    } else {
        d->tail = d->tail->prev;

        if (d->tail)
            d->tail->next = NULL;
        else
            d->head = NULL;
    }

    free(tmp);
    return value;
}

bool is_empty(Deque *d) {
    return d->head == NULL;
}
