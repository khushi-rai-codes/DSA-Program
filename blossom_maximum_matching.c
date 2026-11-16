#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 505

int n, m;
int graph[MAXN][MAXN];
int match[MAXN], parent[MAXN], base[MAXN];
int used[MAXN], blossom[MAXN], queue[MAXN];

int lca(int a, int b) {
    int seen[MAXN] = {0};

    while (1) {
        a = base[a];
        seen[a] = 1;

        if (match[a] == 0)
            break;

        a = parent[match[a]];
    }

    while (1) {
        b = base[b];

        if (seen[b])
            return b;

        b = parent[match[b]];
    }
}

void mark_path(int v, int b, int child) {
    while (base[v] != b) {
        blossom[base[v]] = 1;
        blossom[base[match[v]]] = 1;

        parent[v] = child;
        child = match[v];
        v = parent[match[v]];
    }
}

int find_augmenting_path(int root) {
    memset(used, 0, sizeof(used));
    memset(parent, 0, sizeof(parent));

    for (int i = 1; i <= n; i++)
        base[i] = i;

    int head = 0, tail = 0;
    queue[tail++] = root;
    used[root] = 1;

    while (head < tail) {
        int v = queue[head++];

        for (int u = 1; u <= n; u++) {
            if (!graph[v][u] || base[v] == base[u] ||
                match[v] == u)
                continue;

            if (u == root ||
                (match[u] != 0 && parent[match[u]] != 0)) {

                int current_base = lca(v, u);

                memset(blossom, 0, sizeof(blossom));

                mark_path(v, current_base, u);
                mark_path(u, current_base, v);

                for (int i = 1; i <= n; i++) {
                    if (blossom[base[i]]) {
                        base[i] = current_base;

                        if (!used[i]) {
                            used[i] = 1;
                            queue[tail++] = i;
                        }
                    }
                }
            } else if (parent[u] == 0) {
                parent[u] = v;

                if (match[u] == 0)
                    return u;

                int next = match[u];
                used[next] = 1;
                queue[tail++] = next;
            }
        }
    }

    return 0;
}

int maximum_matching(void) {
    memset(match, 0, sizeof(match));

    int answer = 0;

    for (int i = 1; i <= n; i++) {
        if (match[i] != 0)
            continue;

        int v = find_augmenting_path(i);

        if (v == 0)
            continue;

        answer++;

        while (v != 0) {
            int previous = parent[v];
            int next = match[previous];

            match[v] = previous;
            match[previous] = v;

            v = next;
        }
    }

    return answer;
}

int main(void) {
    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &m);

    if (n <= 0 || n >= MAXN || m < 0) {
        printf("Invalid graph size.\n");
        return 1;
    }

    printf("Enter edges (u v):\n");

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u < 1 || u > n || v < 1 || v > n) {
            printf("Invalid edge.\n");
            return 1;
        }

        graph[u][v] = graph[v][u] = 1;
    }

    int result = maximum_matching();

    printf("\nMaximum matching size: %d\n", result);
    printf("Matched pairs:\n");

    for (int i = 1; i <= n; i++) {
        if (match[i] > i)
            printf("%d -- %d\n", i, match[i]);
    }

    return 0;
}
