#include <stdio.h>
#include <stdlib.h>

int **make_matrix(int size) {
	int i;
	int **matrix;
	
	matrix = (int**) malloc(size * sizeof(int*));
	
	for (i = 0; i < size; i++) {
		matrix[i] = (int*) malloc(size * sizeof(int));
	}
	
	return matrix;
	
}

void read_matrix(int **matrix, int size) {
	int i, j, n;
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			scanf("%d", &n);
			
			matrix[i][j] = n;
		}
	}
}

void free_matrix(int **matrix, int size) {
	int i;
	
	for (i = 0; i < size; i++) free(matrix[i]);
	
	free(matrix);
}

int is_bipartitionable(int **matrix, int size) {
	int vertex;
	int i;
	int head = 0, tail = 1;
	int *queue = (int*) malloc(size * sizeof(int));
	int *groups = (int*) malloc(size * sizeof(int));
	
	for (i = 0; i < size; i++) groups[i] = -1;
	
	groups[0] = 0;
	queue[head] = 0;
	
	
	while (head < tail) {
		vertex = queue[head++];
		
		for (i = 0; i < size; i++) {
			if (!matrix[vertex][i]) {
				if (groups[i] == -1) {
					queue[tail++] = i;
					groups[i] = !groups[vertex];
					continue;
				}
	
				if (groups[i] == groups[vertex]) {
					free(queue);
					free(groups);
					return 0;
				}
			}
		}
	}
	
	free(queue);
	free(groups);

	return 1;
}

int main(int argc, char *argv[]) {
	int n;
	int **matrix;

	scanf("%d", &n);
	
	matrix = make_matrix(n);

	read_matrix(matrix, n);	

	if (is_bipartitionable(matrix, n)) {
		printf("Bazinga!\n");
	} else {
		printf("Fail!\n");
	}

	return 0;
}
