#include <stdio.h>
#include <stdlib.h>

int **graph;
int *degree;
int cuts;

int dfs_mod(int node, int parent, int *values, int k) {
    long long acc = values[node]; 
    for (int i = 0; i < degree[node]; ++i) {
        int nxt = graph[node][i];
        if (nxt == parent) continue;
        int child_mod = dfs_mod(nxt, node, values, k);
       
        if (child_mod == 0) {
            ++cuts;
        } else {
            acc += child_mod;
        }
    }
    return (int)(acc % k);
}

int maxKDivisibleComponents(int n, int** edges, int edgesSize,
                            int* edgesColSize, int* values, int valuesSize, int k) {
    if (n <= 0) return 0;
 
    graph = (int**)malloc(sizeof(int*) * n);
    degree = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        int a = edges[i][0], b = edges[i][1];
        ++degree[a];
        ++degree[b];
    }
    for (int i = 0; i < n; ++i) {
        graph[i] = (int*)malloc(sizeof(int) * (degree[i] == 0 ? 0 : degree[i]));
        degree[i] = 0;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int a = edges[i][0], b = edges[i][1];
        graph[a][degree[a]++] = b;
        graph[b][degree[b]++] = a;
    }

    long long total = 0;
    for (int i = 0; i < n; ++i) total += values[i];
    if (k == 0) {
        return 0;
    }
    if (total % k != 0) {
        return 0;
    }

    cuts = 0;
    dfs_mod(0, -1, values, k);

    return cuts + 1;
}
