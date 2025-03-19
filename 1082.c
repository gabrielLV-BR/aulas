#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct node_t {
	int value;
	struct node_t *next;
} node;

typedef struct graph_t {
	int vertex_count;
	node **vertices;
} graph;

graph make_graph(int vertex_count) {
	graph g;
	
	g.vertex_count = vertex_count;
	g.vertices = (node**) calloc(vertex_count, sizeof(node*));
	
	return g;
}

void add_directed_relation(graph g, int start, int end) {
	node *n = (node*) malloc(sizeof (node));
	
	n->value = end;
	n->next = g.vertices[start];

	g.vertices[start] = n;
}

void add_relation(graph g, int a, int b) {
	add_directed_relation(g, a, b);
	add_directed_relation(g, b, a);
}

void sort(char *values, int length) {
	int i, sorted;
	char aux;
	
	do {
		sorted = 1;
		
		for (i = 1; i < length; i++) {
			if (values[i] < values[i - 1]) {
				aux = values[i];
				values[i] = values[i - 1];
				values[i - 1] = aux;
			}
		}
	} while (!sorted);
	
}

void bfs(graph g, int starting_vertex, int *vertices) {
	int i;
	int head = 0, tail = 1;
	char *queue = malloc(sizeof(char) * g.vertex_count);
	node *n;

	queue[head] = starting_vertex;
	vertices[starting_vertex] = 0;
	
	while (head < tail) {
		n = g.vertices[queue[head++]];
		
		while (n) {
			if (vertices[n->value] == -1) {
				queue[tail++] = n->value;
				vertices[n->value] = 1;
			}

			n = n->next;
		}
	}
	
	// sort them
	
	sort(queue, tail);
	
	for (head = 0; head < tail; head++) {
		printf("%c,", queue[head] + 'a');
	}
	putchar('\n');
	
	free(queue);
}

int main(int argc, char *argv[]) {
	int vertex_count, edge_count, i;
	int current_test_case, test_case_count;
	int next_vertex;
	char vertex_1, vertex_2;
	int *vertices;
	int connected_components;

	graph g;

	scanf("%d", &test_case_count);
	putchar('\n');
	
	for (current_test_case = 0; current_test_case < test_case_count; current_test_case++) {
		connected_components = 0;
	
		scanf("%d %d", &vertex_count, &edge_count);
		putchar('\n');
		 
		g = make_graph(vertex_count);
		vertices = malloc(sizeof(int) * vertex_count);
		
		for (i = 0; i < vertex_count; i++) vertices[i] = -1;
	
		while (edge_count--) {		
			fflush(stdin);
			scanf("%c %c", &vertex_1, &vertex_2);

			add_relation(g, (int)vertex_1 - 'a', (int)vertex_2 - 'a');
		}
		
		printf("Case #%d:\n", current_test_case + 1);
		
		for (next_vertex = 0; next_vertex < g.vertex_count; next_vertex++) {
			if (vertices[next_vertex] != -1) {
				continue;	
			}
			
			connected_components++;
			bfs(g, next_vertex, vertices);
		}
		
		printf("%d connected components\n", connected_components);
		
		free(g.vertices);
		free(vertices);
	}
}
