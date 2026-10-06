#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int discovery[MAX];
int low[MAX];
int stack[MAX];
int inStack[MAX];

int timeCounter = 0;
int stackTop = -1;
int vertices;

void push(int vertex) {
    stack[++stackTop] = vertex;
    inStack[vertex] = 1;
}

int pop() {
    int vertex = stack[stackTop--];
    inStack[vertex] = 0;
    return vertex;
}

void printSCC(int root) {
    printf("{ ");

    while (1) {
        int vertex = pop();
        printf("%d ", vertex);

        if (vertex == root) {
            break;
        }
    }

    printf("}\n");
}

void tarjanDFS(int vertex) {
    discovery[vertex] = low[vertex] = ++timeCounter;

    push(vertex);

    for (int next = 0; next < vertices; next++) {
        if (!graph[vertex][next]) {
            continue;
        }

        if (discovery[next] == 0) {
            tarjanDFS(next);

            if (low[next] < low[vertex]) {
                low[vertex] = low[next];
            }
        }
        else if (inStack[next]) {
            if (discovery[next] < low[vertex]) {
                low[vertex] = discovery[next];
            }
        }
    }

    if (low[vertex] == discovery[vertex]) {
        printSCC(vertex);
    }
}

void tarjanSCC() {
    for (int i = 0; i < vertices; i++) {
        discovery[i] = 0;
        low[i] = 0;
        inStack[i] = 0;
    }

    timeCounter = 0;
    stackTop = -1;

    printf("Strongly Connected Components:\n");

    for (int i = 0; i < vertices; i++) {
        if (discovery[i] == 0) {
            tarjanDFS(i);
        }
    }
}

int main() {
    vertices = 8;

    graph[0][1] = 1;
    graph[1][2] = 1;
    graph[2][0] = 1;

    graph[2][3] = 1;

    graph[3][4] = 1;
    graph[4][5] = 1;
    graph[5][3] = 1;

    graph[5][6] = 1;
    graph[6][7] = 1;
    graph[7][6] = 1;

    tarjanSCC();

    return 0;
}
