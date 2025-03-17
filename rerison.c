#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    int value;
    struct node_t *next;
} node;

typedef struct graph_t {
    int vertex_count;
    node **vertices;
} graph;

graph make_graph(int vertex_count) {
    graph g = {};

    g.vertex_count = vertex_count;
    g.vertices = (node**) calloc(vertex_count, sizeof (node*));

    return g;
}

void add_relation(graph g, int a, int b) {
    node *n = (node*) malloc(sizeof(node));

    n->value = b;
    n->next = g.vertices[a];
    g.vertices[a] = n;
}

void calculate_distances(graph g, int starting_vertex, int *distances) {
    node *n;
    int i, head = 0, tail = 1;
    int *queue = (int*) calloc(g.vertex_count, sizeof(int));

    // limpa lista de distâncias
    for (i = 0; i < g.vertex_count; i++) {
        distances[i] = -1;
    }

    // inicializa primeiro vértice
    queue[head] = starting_vertex;
    distances[starting_vertex] = 0;

    // enquanto houver elementos na fila...
    while (head < tail) {
        // ...pop...
        n = g.vertices[queue[head]];

        // ...pra cada vértice adjacente...
        while (n) {
            // ...setta distância e insere na fila
            // (adicionamos verificação para garantirmos a menor distância)
            if (distances[n->value] == -1 || distances[n->value] > distances[head]) {
                distances[n->value] = distances[head] + 1;
                queue[tail++] = n->value;
            }

            n = n->next;
        }

        head++;
    }

}

int add_name(char **names, const char* name) {
    int i;

    for (i = 0; names[i] != NULL; i++) {
        if (strcmp(name, names[i]) == 0) {
            return i;
        }
    }
    
    names[i] = (char*) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(names[i], name);
    
    return i;
}

int add_name_pair(graph g, char **names) {
    int i = 0;

    static char name_1[100];
    static char name_2[100];

    fscanf(stdin, "%s %s", name_1, name_2);

    // adiciona as relações
    int first_vertex = add_name(names, name_1);
    int second_vertex = add_name(names, name_2);

    add_relation(g, first_vertex, second_vertex);
}

void remove_distant_names(char **names, int *distances, int max_distance) {
    int i;

    for (i = 0; names[i] != NULL; i++) {
        if (distances[i] > max_distance) {
            free(names[i]);
            names[i] = NULL;
        }
    }
}

int comes_before(const char *name_1, const char *name_2) {
    return name_1[0] < name_2[0];
}

void sort_names(char **names) {
    int i, sorted;
    char *aux;

    do {
        sorted = 1;

        for (i = 1; names[i] != NULL; i++) {
            if (names[i - 1] == NULL || comes_before(names[i], names[i - 1])) {
                aux = names[i];
                names[i] = names[i - 1];
                names[i - 1] = aux;
                sorted = 0;
            }
        }
    } while(!sorted);
}

void print_names(const char** names) {
    int i = 0, count = 0;

    // count people
    while (names[i++] != NULL);

    count = i - 1;

    // mostra quantidade de convidados
    printf("%d\n", count);

    // mostra nome dos convidados
    for (i = 0; i < count; i++) {
        printf("%s\n", names[i]);
    }
}

int main() {
    int i;
    int rerisson;
    int num_relations, max_degree;

    graph g;
    char **names;
    int *distances;

    fscanf(stdin, "%d %d", &num_relations, &max_degree);
    
    g = make_graph(num_relations * 2);
    distances = (int*) malloc(g.vertex_count * sizeof(int));

    names = (char**) calloc(num_relations * 2, sizeof (char*));
    
    for (i = 0; i < num_relations; i++) {
        add_name_pair(g, names);
    }
    
    rerisson = add_name(names, "Rerisson");

    calculate_distances(g, rerisson, distances);

    // clear rerrison
    distances[rerisson] = max_degree + 1;

    remove_distant_names(names, distances, max_degree);
    sort_names(names);

    print_names(names);
}
