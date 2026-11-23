#include <stdio.h>

#define MAXN 1005

typedef struct {
    int child[2];
    int parent;
    int reverse;
    int value;
    int sum;
} Node;

Node tree[MAXN];

int isRoot(int x) {
    int p = tree[x].parent;

    return p == 0 ||
        (tree[p].child[0] != x &&
         tree[p].child[1] != x);
}

void update(int x) {
    tree[x].sum = tree[x].value;

    if (tree[x].child[0])
        tree[x].sum += tree[tree[x].child[0]].sum;

    if (tree[x].child[1])
        tree[x].sum += tree[tree[x].child[1]].sum;
}

void pushReverse(int x) {
    if (!x) return;

    int temp = tree[x].child[0];
    tree[x].child[0] = tree[x].child[1];
    tree[x].child[1] = temp;

    tree[x].reverse ^= 1;
}

void pushDown(int x) {
    if (tree[x].reverse) {
        pushReverse(tree[x].child[0]);
        pushReverse(tree[x].child[1]);
        tree[x].reverse = 0;
    }
}

void rotate(int x) {
    int p = tree[x].parent;
    int g = tree[p].parent;

    int direction = (tree[p].child[1] == x);
    int middle = tree[x].child[direction ^ 1];

    if (!isRoot(p))
        tree[g].child[tree[g].child[1] == p] = x;

    tree[x].parent = g;

    tree[x].child[direction ^ 1] = p;
    tree[p].parent = x;

    tree[p].child[direction] = middle;

    if (middle)
        tree[middle].parent = p;

    update(p);
    update(x);
}

void pushPath(int x) {
    static int stack[MAXN];
    int top = 0;

    stack[top++] = x;

    for (int y = x; !isRoot(y); ) {
        y = tree[y].parent;
        stack[top++] = y;
    }

    while (top)
        pushDown(stack[--top]);
}

void splay(int x) {
    pushPath(x);

    while (!isRoot(x)) {
        int p = tree[x].parent;
        int g = tree[p].parent;

        if (!isRoot(p)) {
            if ((tree[p].child[0] == x) ==
                (tree[g].child[0] == p))
                rotate(p);
            else
                rotate(x);
        }

        rotate(x);
    }

    update(x);
}

void access(int x) {
    int last = 0;

    for (int y = x; y; y = tree[y].parent) {
        splay(y);

        tree[y].child[1] = last;

        if (last)
            tree[last].parent = y;

        update(y);
        last = y;
    }

    splay(x);
}

void makeRoot(int x) {
    access(x);
    pushReverse(x);
}

int findRoot(int x) {
    access(x);

    while (tree[x].child[0]) {
        pushDown(x);
        x = tree[x].child[0];
    }

    splay(x);
    return x;
}

int link(int x, int y) {
    makeRoot(x);

    if (findRoot(y) == x)
        return 0;

    tree[x].parent = y;
    return 1;
}

int cut(int x, int y) {
    makeRoot(x);
    access(y);

    if (tree[y].child[0] != x ||
        tree[x].child[1] != 0)
        return 0;

    tree[y].child[0] = 0;
    tree[x].parent = 0;

    update(y);
    return 1;
}

int pathSum(int x, int y) {
    makeRoot(x);
    access(y);

    return tree[y].sum;
}

int main() {
    int n = 5;

    int values[] = {0, 10, 20, 30, 40, 50};

    for (int i = 1; i <= n; i++) {
        tree[i].value = values[i];
        tree[i].sum = values[i];
    }

    link(1, 2);
    link(2, 3);
    link(3, 4);
    link(4, 5);

    printf("Path sum from 1 to 5: %d\n",
           pathSum(1, 5));

    printf("Cut edge (3, 4): %s\n",
           cut(3, 4) ? "Successful" : "Failed");

    printf("Link 2 and 5: %s\n",
           link(2, 5) ? "Successful" : "Failed");

    printf("New path sum from 1 to 5: %d\n",
           pathSum(1, 5));

    return 0;
}
