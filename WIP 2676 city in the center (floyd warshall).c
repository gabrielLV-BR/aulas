#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 100000
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int **make_graph(int n) {
	int i;
	int **graph = (int**) malloc(n * sizeof(int*));
	
	for (i = 0; i < n; i++) {
		graph[i] = (int*) calloc(n, sizeof(int));
	}	
	
	return graph;
}

void free_graph(int** graph, int n) {
	int i;

	if (!graph) {
		return;
	}
	
	for (i = 0; i < n; i++) {
		free(graph[i]);
	}

	free(graph);
}

void print_matrix(int **matrix, int n) {
	int i, j;
	
	for (i = 0; i < n; i++) printf("%2d\t", i);
	
	putchar('\n');
	
	for (i = 0; i < n; i++) {	
		printf("%d\t[", i);
	
		for (j = 0; j < n; j++) {
			printf("%2d\t", matrix[i][j]);
		}
	
		putchar('\n');		
	}
}

void floyd_warshall(int **graph, int n) {
	int i, j, k;
	int sum_distance;
	int min_distance = INF;
	

	// initialize distances
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			// isso aqui não faz sentido
			if (!graph[i][j]) {
				graph[i][j] = INF;
			}
		}
	}
	
		print_matrix(graph, n);
	
	// freaky calculations
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				graph[i][j] = MIN(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
	
	k = 0;
	
	for (i = 0; i < n; i++) {
		sum_distance = 0;
	
		for (j = 0; j < n; j++) {
			sum_distance += graph[i][j];		
		}
		
		if (sum_distance != 0 && sum_distance < min_distance) {
			min_distance = sum_distance;
			k = i;	
		}
	}
	
	if (min_distance == INF) {
		printf("-1\n");
		return;
	}
	
	for (i = 0; i < n; i++) {
		sum_distance = 0;
	
		for (j = 0; j < n; j++) {
			sum_distance += graph[i][j];			
		}
		
		if (sum_distance == min_distance) {
			printf("%d ", i);
		}
	}
}

int main(int argc, char *argv[]) {
	int i;
	int num_cities, num_roads;
	int vertex_a, vertex_b, distance;
	int **graph = NULL;

	do {
		free_graph(graph, num_cities);
	
		scanf("%d %d", &num_cities, &num_roads);
		
		if (num_cities == 0 && num_roads == 0) {
			break;
		}	
		
		graph = make_graph(num_cities);
		
		for (i = 0; i < num_roads; i++) {
			scanf("%d %d %d", &vertex_a, &vertex_b, &distance);
			printf("[%d][%d] = %d\n", vertex_a, vertex_b, distance);
			vertex_a--;
			vertex_b--;
			graph[vertex_a][vertex_b] = distance;
			graph[vertex_b][vertex_a] = distance;
		}
		
		floyd_warshall(graph, num_cities);
	} while (1);

	return 0;
}
