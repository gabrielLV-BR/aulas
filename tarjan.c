/**
 * Muito obrigado professor Cadinho.
 * O senhor é muito foda e metal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define SET_ALL(list,count,value) do { int _i_; for (_i_ = 0; _i_ < (count); _i_++) (list)[_i_] = (value); } while(0)
#define UNDEFINED(x) ((x)==(-1))
#define MIN(x,y) ((x)<(y)?(x):(y))

typedef struct connected_component_t {
    int vertex_count;
    int *vertices;
} connected_component;

typedef struct connected_component_node_t {
    connected_component component;    
    struct connected_component_node_t *next;
} connected_component_node;

int matrix[N][N];
int stack[N];
int visited[N];
int indices[N];
int low[N];
int on_stack[N];
int head = 0;
int global_counter = 0;
connected_component_node *connected_components = NULL;

void clear_matrix() {
    int i;

    for (i = 0; i < N; i++) {
        SET_ALL(matrix[i], N, 0);
    }
}

void print_matrix() {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%2d\t", matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void print_connected_component(connected_component component) {
    int i;

    for (i = 0; i < component.vertex_count; i++) {
        printf("%d", component.vertices[i]);

        if (i != (component.vertex_count - 1)) {
            printf(" - ");
        }
    }
    putchar('\n');
}

void print_connected_components() {
    int i = 0;
    connected_component_node *node = connected_components;

    while (node->next) {
        printf("Componente conexa %d\n", i++);
        print_connected_component(node->component);
        node = node->next;
    }
}

void clear_stack() {
    SET_ALL(stack, N, 0);
    SET_ALL(on_stack, N, 0);
    head = 0;
}

void clear_visited() {
    SET_ALL(visited, N, 0);
}

void clear_global_counter() {
    global_counter = 0;
}

void clear_low_list() {
    SET_ALL(low, N, -1);
}

void clear_indices() {
    SET_ALL(indices, N, -1);
}

void stack_push(int n) {
    stack[head++] = n;
    on_stack[n] = 1;
}

int stack_empty() {
    return head > 0;
}

int stack_pop() {
    int value = stack[--head];

    on_stack[value] = 0;

    return value;
}

int stack_find(int n) {
    int i;

    for (i = 0; i < N; i++) {
        if (stack[i] == n) {
            return i;
        }
    }

    return -1;
}

int dfs(int vertex) {
    int w, i;

    visited[vertex] = 1;
    indices[vertex] = global_counter;
    low[vertex] = global_counter;
    global_counter++;

    stack_push(vertex);

    for (w = 0; w < N; w++) {
        if (!matrix[vertex][w]) {
            continue;
        }

        if (UNDEFINED(indices[w])) {
            dfs(w);
            low[vertex] = MIN(low[vertex], low[w]);
        } else if (on_stack[w]) {
            low[vertex] = MIN(low[vertex], indices[w]);
        }
    }

    if (indices[vertex] == low[vertex]) {
        connected_component component;
        connected_component_node *node = (connected_component_node*) malloc(sizeof component);

        component.vertex_count = 0;
        component.vertices = (int*) malloc(N * sizeof(int));

        i = 0;

        do {
            w = stack_pop();
            component.vertices[i++] = w;
        } while (w != vertex);

        component.vertex_count = i;

        printf("Componente conexa.\n");
        print_connected_component(component);

        node->component = component;
        node->next = connected_components;

        connected_components = node;
    }
}

int tarjan() {
    int i;

    clear_stack();
    clear_visited();
    clear_indices();
    clear_global_counter();

    for (i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    clear_matrix();

// Componente 1
matrix[0][1] = 1;
matrix[1][0] = 1;
matrix[1][2] = 1;
matrix[2][1] = 1;
matrix[2][3] = 1;
matrix[3][2] = 1;

// Componente 2
matrix[4][5] = 1;
matrix[5][4] = 1;
matrix[5][6] = 1;
matrix[6][5] = 1;

// Componente 3
matrix[7][8] = 1;
matrix[8][7] = 1;
matrix[8][9] = 1;
matrix[9][8] = 1;
matrix[9][10] = 1;
matrix[10][9] = 1;
matrix[10][11] = 1;
matrix[11][10] = 1;
matrix[11][12] = 1;
matrix[12][11] = 1;
matrix[12][13] = 1;
matrix[13][12] = 1;

// Componente 4
matrix[14][15] = 1;
matrix[15][14] = 1;
matrix[15][16] = 1;
matrix[16][15] = 1;
matrix[16][17] = 1;
matrix[17][16] = 1;
matrix[18][19] = 1;
matrix[19][18] = 1;

// Arestas que conectam os componentes
matrix[3][4] = 1;
matrix[6][7] = 1;
matrix[9][10] = 1;
matrix[13][14] = 1;
matrix[17][18] = 1;

/*
4 6
0 1
1 2
2 3
3 0
0 2
2 0

*/
    printf("Tarjan\n");
    tarjan();

    // printf("Printing connected components\n");
    // print_connected_components();

    // printf("Printing matrix\n");
    // print_matrix();
}
