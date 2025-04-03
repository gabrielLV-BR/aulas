#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BIG INT_MAX
#define N 4

typedef struct edge_t {
	int origin, target;
	int weight;
} edge;

edge make_edge(int origin, int target, int weight) {
	edge e;
	e.origin = origin;
	e.target = target;
	e.weight = weight;
	return e;
}

int bellman_ford(edge* edges, int edge_count, int origin, int target) {
	int i, j;
	int *distances = (int*) calloc(edge_count, sizeof(int));
	int *parent = (int*) malloc(edge_count * sizeof(int));
	
	for (i = 0; i < edge_count; i++) {
		distances[i] = BIG;
		parent[i] = -1;	
	}

	distances[origin] = 0;
	
	for (i = 0; i < edge_count - 1; i++) {
		for (j = 0; j < edge_count; j++) {
			edge e = edges[j];

			if (distances[e.target] > (distances[e.origin] + e.weight)) {
				distances[e.target] = distances[e.origin] + e.weight;
				parent[e.target] = e.origin;
			}
		}
	}
	
	for (j = 0; j < edge_count; j++) {
		edge e = edges[j];
		int edge_distance = distances[e.origin] + e.weight;

		if (distances[e.target] > edge_distance) {
			printf("Ciclo negativo encontrado!");
			return -1;
		}
	}
	
	j = target;
	
	int head = 0;
	int *fullpath = malloc(edge_count * sizeof(int));
	
	while (j != -1) {
		fullpath[head++] = j;
		j = parent[j];
	}
	
	for (j = head - 1; j >= 0; j--) {
		printf("%d", fullpath[j]);
		if ((j - 1) >= 0) {
			printf(" -> ");
		}
	}
	
	putchar('\n');
	
	return distances[target];
}

int main(int argc, char *argv[]) {
	int i = 0;
	int source = 0;
	int target = 3;
	
	edge *edges = (edge*) malloc(100 * sizeof(edge));
	
	edges[i++] = make_edge(0, 1, 2);
	edges[i++] = make_edge(0, 2, 2);
	edges[i++] = make_edge(1, 2, 2);
	edges[i++] = make_edge(2, 3, 4);
	edges[i++] = make_edge(1, 3, 1);
		
	int distance = bellman_ford(edges, i, source, target);

	printf("Menor distancia entre %d e %d: %d\n", source, target, distance);
	return 0;
}
