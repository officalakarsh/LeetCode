#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10007  

typedef struct Node {
    int key;
    int index;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

int hash(int key) {
    if (key < 0) key = -key;
    return key % HASH_SIZE;
}

void insert(int key, int index) {
    int h = hash(key);
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->index = index;
    node->next = hashTable[h];
    hashTable[h] = node;
}

int search(int key) {
    int h = hash(key);
    Node* curr = hashTable[h];
    while (curr) {
        if (curr->key == key)
            return curr->index;
        curr = curr->next;
    }
    return -1;
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = NULL;

    int* result = (int*)malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int idx = search(complement);

        if (idx != -1) {
            result[0] = idx;
            result[1] = i;
            *returnSize = 2;
            return result;
        }
        insert(nums[i], i);
    }

    *returnSize = 0;
    return result;
}
