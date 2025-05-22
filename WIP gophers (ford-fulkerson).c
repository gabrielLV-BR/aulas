#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ONE ((edge) {1, 1})

typedef struct position_t {
    float x, y;
} position;

typedef struct edge_t {
    int capacity, flux;
} edge;

edge** make_matrix(int n) {
    int i;
    edge **matrix;

    matrix = (edge**) malloc(sizeof(edge*) * n);

    for (i = 0; i < n; i++) {
        matrix[i] = (edge*) calloc(n, sizeof(edge));
    }

    return matrix;
}

position* read_positions(int count) {
    int i;
    position* positions = (position*) calloc(count, sizeof(position));

    for (i = 0; i < count; i++) {
        scanf("%f %f", &positions[i].x, &positions[i].y);
        printf("Lido %f %f\n", positions[i].x, positions[i].y);
    }

    return positions;
}

void print_matrix(edge **matrix, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j].capacity);
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

    for (g = 0; g < gopher_count; g++) {
        for (h = 0; h < hole_count; h++) {
            dist = distance(gophers[g], holes[h]);

            int gopher = g;
            int hole = h + gopher_count;

            printf("[%d](%f, %f) - (%f) -> [%d](%f, %f)\n",
                gopher, gophers[gopher].x, gophers[gopher].y,
                dist,
                hole, holes[hole].x, holes[hole].y);

            if ((velocity * seconds) >= dist) {
                matrix[gopher][hole] = ONE;
                matrix[hole][gopher] = ONE;
            }
        }
    }

    int origin = gopher_count + hole_count;
    int target = gopher_count + hole_count + 1;
    // link origin vertex to all gophers
    for (g = 0; g <= gopher_count; g++) {
        matrix[origin][g] = ONE;
    }

    // link all holes to target vertex
    for (h = 0; h <= hole_count; h++) {
        matrix[h][target] = ONE;
    }
}

int main() {
    int i;
    int gopher_count, hole_count;
    float seconds, velocity;
    position *holes;
    position *gophers;
    
    edge **matrix;

    scanf("%d %d %f %f", &gopher_count, &hole_count, &seconds, &velocity);

    gophers = read_positions(gopher_count);
    holes = read_positions(hole_count);

    matrix = make_matrix(hole_count + gopher_count + 2);

    link_gophers_to_holes(
        matrix,
        gophers, gopher_count,
        holes, hole_count,
        seconds, velocity);

    print_matrix(matrix, gopher_count + hole_count + 2);

    free(gophers);
    free(holes);
}
