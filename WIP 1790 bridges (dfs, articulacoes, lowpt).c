#include <stdio.h>
#include <stdlib.h>

int **make_matrix(int size) {
	int i;
	int **matrix;

	matrix = (int**) malloc(size * sizeof(int));
	
	for (i = 0; i < size; i++) {
		matrix[i] = (int*) calloc(size, sizeof(int));
	}

	return matrix;
}

void dfs(
	int **matrix,
	int *depths,
	int matrix_size,
	int vertex,
	int depth)
{
	int i;
	
	for (i = 0; i < matrix_size; i++) {
		if (matrix[vertex][i] && depths[i] == -1) {
			depths[i] = depth;
			
			matrix[vertex][i] = 2;
			matrix[i][vertex] = 0;
			
			dfs(matrix, depths, matrix_size, i, depth + 1);
		}
	}
}

int main() {
	int **matrix, *depth;
	int num_vertices, num_edges;
	int edge_a, edge_b;
	int i, j;
	int count;
	
	scanf("%d %d", &num_vertices, &num_edges);
	
	matrix = make_matrix(num_vertices);
	depth = malloc(num_vertices * sizeof(int));
	
	for (i = 0; i < num_vertices; i++) depth[i] = -1;

	while (num_edges--) {
		scanf("%d %d", &edge_a, &edge_b);
		edge_a--;
		edge_b--;
		matrix[edge_a][edge_b] = 1;	
	}
	
	dfs(matrix, depth, num_vertices, 0, 0);

	count = 0;
	for (i = 0; i < num_vertices; i++) {
		for (j = 0; j < num_vertices; j++) {
			if (matrix[i][j] && matrix[i][j] != 2) count++;
		}		
	}
	
	printf("%d\n", count);
	
	return 0;
}
