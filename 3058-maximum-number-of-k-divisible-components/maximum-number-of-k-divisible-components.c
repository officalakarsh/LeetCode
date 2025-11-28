#include <stdio.h>
#include <stdlib.h>

int **graph;
int *degree;
int cuts; // number of edges we can cut

// DFS returns (subtree sum) % k
int dfs_mod(int node, int parent, int *values, int k) {
    long long acc = values[node]; // accumulate in 64-bit, then reduce
    for (int i = 0; i < degree[node]; ++i) {
        int nxt = graph[node][i];
        if (nxt == parent) continue;
        int child_mod = dfs_mod(nxt, node, values, k);
        // if child_mod == 0, that child's subtree is divisible by k,
        // so we can cut the edge between node and child.
        if (child_mod == 0) {
            ++cuts;
            // we do not add anything upwards because we cut here
        } else {
            acc += child_mod; // add the remainder part (safe)
        }
    }
    return (int)(acc % k);
}

int maxKDivisibleComponents(int n, int** edges, int edgesSize,
                            int* edgesColSize, int* values, int valuesSize, int k) {
    if (n <= 0) return 0;
    // Build adjacency
    graph = (int**)malloc(sizeof(int*) * n);
    degree = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        int a = edges[i][0], b = edges[i][1];
        ++degree[a];
        ++degree[b];
    }
    for (int i = 0; i < n; ++i) {
        graph[i] = (int*)malloc(sizeof(int) * (degree[i] == 0 ? 0 : degree[i]));
        degree[i] = 0; // reuse as insertion index
    }
    for (int i = 0; i < edgesSize; ++i) {
        int a = edges[i][0], b = edges[i][1];
        graph[a][degree[a]++] = b;
        graph[b][degree[b]++] = a;
    }

    // Total sum check
    long long total = 0;
    for (int i = 0; i < n; ++i) total += values[i];
    if (k == 0) { // defensive: if k==0 problem is undefined; return 0
        return 0;
    }
    if (total % k != 0) {
        // impossible to partition into components each divisible by k
        return 0;
    }

    cuts = 0;
    // Run DFS from node 0 (tree is connected)
    dfs_mod(0, -1, values, k);

    // components = cuts + 1
    return cuts + 1;
}
