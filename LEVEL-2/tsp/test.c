#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <float.h> // For __FLT_MAX__

// Compute the distance between two points
float distance(float a[2], float b[2]) {
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

// Function to calculate the total distance of a path
float calculate_path_distance(float (*array)[2], size_t size, int *order) {
    float total_distance = 0.0f;
    for (size_t i = 0; i < size - 1; i++) {
        total_distance += distance(array[order[i]], array[order[i + 1]]);
    }
    total_distance += distance(array[order[size - 1]], array[order[0]]); // Return to the starting point
    return total_distance;
}

// Function to swap two integers
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Recursive function to generate permutations and find the shortest path
void permute_and_find(float (*array)[2], size_t size, int *order, size_t start, float *shortest_length) {
    if (start == size - 1) {
        float current_length = calculate_path_distance(array, size, order);
        if (current_length < *shortest_length) {
            *shortest_length = current_length;
        }
    } else {
        for (size_t i = start; i < size; i++) {
            swap(order + start, order + i);
            permute_and_find(array, size, order, start + 1, shortest_length);
            swap(order + start, order + i); // backtrack
        }
    }
}

// Main TSP function
float tsp(float (*array)[2], ssize_t size) {
    float shortest_length = __FLT_MAX__;
    int *order = malloc(size * sizeof(int));
    if (!order) {
        fprintf(stderr, "Error: %m\n");
        exit(1);
    }
    for (size_t i = 0; i < size; i++) {
        order[i] = i;
    }
    permute_and_find(array, size, order, 0, &shortest_length);
    free(order);
    return shortest_length;
}

ssize_t file_size(FILE *file) {
    char *buffer = NULL;
    size_t n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int retrieve_file(float (*array)[2], FILE *file) {
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int main(int ac, char **av) {
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1) {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file) {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1) {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof(float[2]));
    if (!array) {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1) {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
}