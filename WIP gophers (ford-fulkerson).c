#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct position_t {
    float x, y;
} position;

typedef struct edge_t {
    int capacity, flux;
} edge;

edge** make_matrix(int width, int height) {
    int i;
    edge **matrix;

    matrix = (edge**) malloc(sizeof(edge*) * height);

    for (i = 0; i < height; i++) {
        // talvez errei a ordem do calloc
        matrix[i] = (edge*) calloc(width, sizeof(edge));
    }

    return matrix;
}

position* read_positions(int count) {
    int i;
    position* positions = (position*) malloc(sizeof(position) * count);

    for (i = 0; i < count; i++) {
        scanf("%f%f", &positions[i].x, &positions[i].y);
    }

    return positions;
}

void print_matrix(edge **matrix, int width, int height) {
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("(%d, %d)\t", matrix[i][j].capacity, matrix[i][j].flux);
        }
        putchar('\n');
    }
}

float distance(position a, position b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx*dx + dy*dy);
}

void link_gophers_to_holes( 
    edge** matrix,                            
    position *gophers, int gopher_count,
    position *holes, int hole_count,
    float seconds, float velocity)
{
    int g, h;
    float dist;

    for (g = 1; g <= gopher_count; g++) {
        for (h = 1; h <= hole_count; h++) {
            if ((velocity * seconds) >= distance(gophers[g], holes[h])) {
                matrix[g][h].capacity = 1;
                matrix[g][h].flux = 1;
            }
        }
    }

    // link origin vertex to all gophers
    for (g = 0; g <= gopher_count; g++) {
        matrix[0][g] = (edge) { 1, 1 };
    }

    // link all holes to target vertex
    for (h = 0; h <= hole_count; h++) {
        matrix[h][0] = (edge) { 1, 1 };
    }
}

int main() {
    int i;
    int gopher_count, hole_count;
    float seconds, velocity;
    position *holes;
    position *gophers;
    
    edge **matrix;

    scanf("%d%d%f%f", &gopher_count, &hole_count, &seconds, &velocity);

    gophers = read_positions(gopher_count);
    holes = read_positions(hole_count);

    matrix = make_matrix(hole_count + 1, gopher_count + 1);

    link_gophers_to_holes(
        matrix,
        gophers, gopher_count,
        holes, hole_count,
        seconds, velocity);

    print_matrix(matrix, gopher_count + 1, hole_count + 1);

    free(gophers);
    free(holes);
}