#include <stdio.h>
#include <stdlib.h>

#define MAX 1000


typedef struct node_t {
	int value;
	struct node_t *next;
} node;

typedef struct graph_t {
	int num_vertices;
	node **vertices;
} graph;

graph make_graph(int num_vertices) {
	graph g;
	
	g.num_vertices = num_vertices;
	g.vertices = (node **) calloc(num_vertices, sizeof(node *));
	
	return g;
}

node* make_node(int vertex) {
	node *n = (node*) malloc(sizeof(node));
	
	n->next = NULL;
	n->value = vertex;

	return n;
}

void insert_relation_directed(graph g, int origin, int destination) {
	node *n = make_node(destination);
	n->next = g.vertices[origin];
	g.vertices[origin] = n;	
}

void insert_relation(graph g, int a, int b) {
	insert_relation_directed(g, a, b);
	insert_relation_directed(g, b, a);
}

void print_relations(graph g) {
	int i;
	node *n;

	for (i = 0; i < g.num_vertices; i++) {
		printf("%d ", i);

		n = g.vertices[i];
		
		while (n) {
			printf("-> %d ", n->value);
			n = n->next;
		}		
		
		putchar('\n');
	}
}

void free_graph(graph g) {
	int i;
	
	for (i = 0; i < g.num_vertices; i++) free(g.vertices[i]);
	
	free(g.vertices);
}

void dfs(graph g, int *visit, int vert) {
	printf("Visiting vertex %d\n", vert);

	visit[vert] = 1;
	node *n = g.vertices[vert];
	
	while (n) {
		if (!visit[vert]) {
			dfs(g, visit, n->value);	
		}
		
		n = n->next;
	}
}

int main(int argc, const char** argv) {
	int i = 1, j;
	
	int test_cases;
	int a, b;
	int roads, covered_roads, uncovered;
	
	graph g;
	int *visited;
	
	sscanf(argv[i++], "%d", &test_cases);
	
	while (test_cases--) {
		printf("Test case number %d\n", test_cases + 1);
		
		sscanf(argv[i++], "%d", &roads);
		sscanf(argv[i++], "%d", &covered_roads);
		
		printf("Roads: %d, covered roads: %d\n", roads, covered_roads);
		
		g = make_graph(roads);

		visited = (int*) calloc(roads, sizeof(int));

		for (j = 0; j < covered_roads; j++) {
			sscanf(argv[i++], "%d %d", &a, &b);
			a--;
			b--;
			
			insert_relation(g, a, b);
		}
		
		for (j = 0; !g.vertices[j] && j < g.num_vertices; j++);
		
		dfs(g, visited, g.vertices[j]->value);
		
		uncovered = 0;
		
		for (j = 0; j < covered_roads; j++) 
			if (!visited[j]) uncovered++;
		
		if (uncovered > 0) {
			printf("Faltam %d estradas\n", uncovered);
		}
		
		free_graph(g);
		free(visited);
	}
}
