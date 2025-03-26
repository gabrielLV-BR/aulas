#include <stdio.h>
#include <stdlib.h>

#define BIG (0x0fffffff)

int mst_price(int **matrix, int matrix_size) {
	int i, j;
	int sum = 0;
	int *subtree = malloc(sizeof(int) * matrix_size);
	int *distances = malloc(sizeof(int) * matrix_size);
	
	for (i = 0; i < matrix_size; i++) {
		subtree[i] = 0;
		distances[i] = BIG; // very big
	}
	
	distances[0] = 0;
	
	for (i = 0; i < matrix_size; i++) {
		int minimum = BIG, closest_vertex;
		
		for (j = 0; j < matrix_size; j++) {
			// vértices adjacentes
			if (
				subtree[j] == 0 // não visitado
				&& distances[j] < minimum // menor visto até agora
			)
			{
				closest_vertex = j;
				minimum = distances[j];
			}
		}
		
		// adiciona à árvore geradora 
		subtree[closest_vertex] = 1;
		
		// atualiza distâncias dos vértices que circundam nóis
		for (j = 0; j < matrix_size; j++) {
			if (
				subtree[j] == 0 // não faz parte da árvore geradora
				&& matrix[closest_vertex][j] != 0
				&& matrix[closest_vertex][j] < distances[j] // menor distância já encontrada
			) {
				distances[j] = matrix[closest_vertex][j];
			}
		}
	}
	
	for (i = 0; i < matrix_size; i++) {
		sum += distances[i];
	}
	
	free(subtree);
	free(distances);
	
	return sum;
}

int main(int argc, char *argv[]) {
	int i;
	int total_price;
	int vertex_count, edge_count;
	int **matrix;
	
	scanf("%d %d", &vertex_count, &edge_count);
	
	matrix = (int**) malloc(sizeof(int*) * vertex_count);
	for (i = 0; i < vertex_count; i++)
		matrix[i] =(int*) calloc(vertex_count, sizeof(int));
		
	while (edge_count--) {
		int vertex_a, vertex_b, weight;
		scanf("%d %d %d", &vertex_a, &vertex_b, &weight);
		vertex_a--;
		vertex_b--;
		matrix[vertex_a][vertex_b] = weight;
		matrix[vertex_b][vertex_a] = weight;
	}
	
	total_price = mst_price(matrix, vertex_count);
	
	printf("%d\n", total_price);

	return 0;
}
