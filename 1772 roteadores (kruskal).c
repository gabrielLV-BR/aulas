#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX(a, b) ((a > b) ? (a) : (b))

typedef struct edge_t {
	int vertex_a;
	int vertex_b;
	int cost;
} edge;

int edge_comparer(const void* a, const void* b) {
	int a_cost = ((edge*) a)->cost;
	int b_cost = ((edge*) b)->cost;
	
	if (a_cost < b_cost) return -1;
	if (a_cost > b_cost) return 1;
	return 0;
}

int kruskal(edge *edges, int edge_count, int *connections, int vertex_count) {
	int i = 0, j;
	int last_edge = 0;
	int total_cost = 0;

	for (i = 0; i < vertex_count; i++) {
		connections[i] = i;
	}

	// sort edges
	qsort(edges, edge_count, sizeof(edge), edge_comparer);
	
	for (j = 0; j < vertex_count - 1; j ++) {
		for (last_edge = 0; last_edge < edge_count; last_edge++) {
			edge to_add = edges[last_edge];
			
			// check if there would be cycles
			// see compare their regions
			int vertex_a_region = connections[to_add.vertex_a];
			int vertex_b_region = connections[to_add.vertex_b];
			
			// if they're on same region...
			if (vertex_a_region == vertex_b_region) {
				// they're already part of the MST
				continue;
			}
			
			// add cost of new relation
			total_cost += to_add.cost;
			
			// incorporate tree onto ours
			for (i = 0; i < vertex_count; i++) {
				if (connections[i] == vertex_a_region) {
					connections[i] = vertex_b_region;
				}
			}
		}
	}
	
	return total_cost;
}

int main(int argc, char *argv[]) {
	int i;
	int edge_list_head = 0;
	int vertex_a, vertex_b, cost;
	int vertex_count, edge_count;

	int *connections;
	edge *edges;
	
	scanf("%d %d", &vertex_count, &edge_count);
	
	edges = (edge*) malloc(edge_count * sizeof(edge));
	connections = (int*) calloc(vertex_count, sizeof(int));
	
	for (i = 0; i < edge_count; i++) {
		scanf("%d %d %d", &vertex_a, &vertex_b, &cost);
		
		edge e;
		e.vertex_a = vertex_a - 1;
		e.vertex_b = vertex_b - 1;
		e.cost = cost;
		
		edges[edge_list_head++] = e;
	}
	
	cost = kruskal(edges, edge_count, connections, vertex_count);	
	
	printf("%d\n", cost);

	free(connections);
	free(edges);
	
	return 0;
}
