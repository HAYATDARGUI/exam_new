/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:35 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/03 18:48:32 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// compute the distance between two points
float   distance(float a[2], float b[2])
{
        return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

// Helper: swap two floats
static void swap(float *a, float *b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

// Helper: swap two 2D points
static void swap_points(float a[2], float b[2])
{
    swap(&a[0], &b[0]);
    swap(&a[1], &b[1]);
}

// Helper: compute total path length including return to start
static float path_length(float (*array)[2], ssize_t size)
{
    float total = 0.0f;
    for (ssize_t i = 0; i < size - 1; i++)
        total += distance(array[i], array[i + 1]);
    total += distance(array[size - 1], array[0]); // Return to start
    return total;
}

// Helper: recursively compute all permutations and track shortest path
static void permute(float (*array)[2], ssize_t start, ssize_t size, float *shortest)
{
    if (start == size)
    {
        float len = path_length(array, size);
        if (len < *shortest)
            *shortest = len;
        return;
    }

    for (ssize_t i = start; i < size; i++)
    {
        swap_points(array[start], array[i]);
        permute(array, start + 1, size, shortest);
        swap_points(array[start], array[i]); // backtrack
    }
}

// Main tsp function
float tsp(float (*array)[2], ssize_t size)
{
    float shortest_length = 9999999.0f; // Large initial value instead of FLT_MAX
    permute(array, 0, size, &shortest_length);
    return shortest_length;
}




// float   tsp(float (*array)[2], ssize_t size)
// {
//   float shortest_length;
//   // ...
//   return (shortest_length);
// }


ssize_t file_size(FILE *file)
{
        char    *buffer = NULL;
        size_t  n = 0;
        ssize_t ret;

        errno = 0;

        for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

        free(buffer);
        if (errno || fseek(file, 0, SEEK_SET))
                return -1;
        return ret;
}

int             retrieve_file(float (*array)[2], FILE *file)
{
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

int             main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
        if (ac > 1)
    {
                filename = av[1];
                file = fopen(filename, "r");
    }

        if (!file)
        {
                fprintf(stderr, "Error opening %s: %m\n", filename);
                return 1;
        }

        ssize_t size = file_size(file);
        if (size == -1)
        {
                fprintf(stderr, "Error reading %s: %m\n", filename);
                fclose(file);
                return 1;
        }

        float (*array)[2] = calloc(size, sizeof (float [2]));
        if (!array)
        {
                fprintf(stderr, "Error: %m\n");
                fclose(file);
                return 1;
        }

        if (retrieve_file(array, file) == -1)
        {
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
