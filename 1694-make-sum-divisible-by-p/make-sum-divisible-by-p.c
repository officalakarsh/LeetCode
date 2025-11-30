#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 200003 

typedef struct Node {
    long long key;
    int value;
    struct Node* next;
} Node;

Node** create_table() {
    Node** table = (Node**) calloc(TABLE_SIZE, sizeof(Node*));
    return table;
}

unsigned int hash_ll(long long x) {
    long long y = x % TABLE_SIZE;
    if (y < 0) y += TABLE_SIZE;
    return (unsigned int) y;
}

void map_put(Node** table, long long key, int value) {
    unsigned int h = hash_ll(key);
    Node* cur = table[h];
    while (cur) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    Node* n = (Node*) malloc(sizeof(Node));
    n->key = key;
    n->value = value;
    n->next = table[h];
    table[h] = n;
}

int map_get(Node** table, long long key) {
    unsigned int h = hash_ll(key);
    Node* cur = table[h];
    while (cur) {
        if (cur->key == key) return cur->value;
        cur = cur->next;
    }
    return -1;
}

void free_table(Node** table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* cur = table[i];
        while (cur) {
            Node* nxt = cur->next;
            free(cur);
            cur = nxt;
        }
    }
    free(table);
}

int minSubarray(int* nums, int numsSize, int p) {
    long long total = 0;
    for (int i = 0; i < numsSize; ++i) total += nums[i];

    int need = (int)(total % p);
    if (need == 0) return 0;

    Node** table = create_table();         
    long long prefix = 0;
    int ans = numsSize;

    map_put(table, 0, 0); 

    for (int i = 0; i < numsSize; ++i) {
        prefix = (prefix + nums[i]) % p;
        if (prefix < 0) prefix += p;

        long long target = (prefix - need) % p;
        if (target < 0) target += p;

        int prev = map_get(table, target);
        if (prev != -1) {
            int len = (i + 1) - prev;
            if (len < ans) ans = len;
        }

        map_put(table, prefix, i + 1);
    }

    free_table(table);

    return (ans == numsSize) ? -1 : ans;
}

