#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define HASH 200003

typedef struct Node {
    long long key;
    long long val;
    struct Node* next;
} Node;

Node* hashTable[HASH];

int getHash(long long x) {
    if (x < 0) x = -x;
    return x % HASH;
}

void insert(long long key, long long val) {
    int h = getHash(key);
    Node* curr = hashTable[h];

    while (curr) {
        if (curr->key == key) {
            curr->val += val;
            return;
        }
        curr = curr->next;
    }

    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->val = val;
    n->next = hashTable[h];
    hashTable[h] = n;
}

long long get(long long key) {
    int h = getHash(key);
    Node* curr = hashTable[h];

    while (curr) {
        if (curr->key == key) return curr->val;
        curr = curr->next;
    }
    return 0;
}

void clearTable() {
    for (int i = 0; i < HASH; i++) {
        Node* curr = hashTable[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        hashTable[i] = NULL;
    }
}


int specialTriplets(int* nums, int numsSize) {
    
    clearTable();

    for (int i = 0; i < numsSize; i++) {
        insert(nums[i], 1);
    }

    long long result = 0;
    long long left[numsSize];
    long long right[numsSize];

    for (int j = 0; j < numsSize; j++) {
        long long target = 2LL * nums[j];
        insert(nums[j], -1);  
        right[j] = get(target);
    }

    clearTable();

    for (int j = 0; j < numsSize; j++) {
        long long target = 2LL * nums[j];
        left[j] = get(target);

        result = (result + (left[j] % MOD) * (right[j] % MOD)) % MOD;

        insert(nums[j], 1);
    }

    return (int)result;
}

