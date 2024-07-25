#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t MAX_LEN = 21, HASH_SIZE = 1000;
static const unsigned int SHIFTS[] = {4, 6, 4, 10};

typedef struct Worker Worker;

bool solve();
bool check(Worker**);
unsigned int hash(char*);
Worker* find(Worker**, char*);

int main(void) {
    printf("%s\n", solve() ? "Yes" : "No");

    return 0;
}

typedef struct Worker {
    char* name;
    int hours;
    Worker* next;
} Worker;

bool solve() {
    int N, tmp;
    scanf("%d", &N);

    char* buf = (char*)malloc(sizeof(char) * MAX_LEN);
    Worker** table = (Worker**)calloc(HASH_SIZE, sizeof(Worker*));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 7; k++) {
                scanf("%s", buf);

                if (strcmp(buf, "-")) {
                    Worker* w = find(table, buf);

                    w->hours += SHIFTS[j];
                }
            }
        }
    }

    bool result = check(table);

    for (int i = 0; i < HASH_SIZE; i++) {
        Worker* cur = table[i];

        while (cur) {
            Worker* tmp = cur;
            cur = cur->next;

            free(tmp->name);
            free(tmp);
        }
    }

    free(buf);
    free(table);

    return result;
}

bool check(Worker** table) {
    int min = -1, max = -1;

    for (int i = 0; i < HASH_SIZE; i++) {
        Worker* cur = table[i];

        while (cur) {
            if (min == -1 || cur->hours < min)
                min = cur->hours;

            if (max == -1 || cur->hours > max)
                max = cur->hours;

            cur = cur->next;
        }
    }

    return (min == -1) || (max - min <= 12);
}

unsigned int hash(char* k) {
    unsigned int h = 5381;
    int c;

    while ((c = *k++))
        h = ((h << 5) + h) + c;

    return h % HASH_SIZE;
}

Worker* find(Worker** table, char* k) {
    unsigned int idx = hash(k);
    Worker* cur = table[idx];

    while (cur) {
        if (strcmp(cur->name, k) == 0)
            return cur;

        cur = cur->next;
    }

    Worker* w = (Worker*)malloc(sizeof(Worker));
    w->name = (char*)malloc(sizeof(char) * MAX_LEN);
    strcpy(w->name, k);
    w->hours = 0;
    w->next = table[idx];

    table[idx] = w;

    return w;
}