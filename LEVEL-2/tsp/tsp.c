/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:35 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/20 11:41:41 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y;
} City;

float distance(City a, City b) {
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main() {
    City cities[11];
    int n = 0;

    // Read input
    while (scanf("%f, %f\n", &cities[n].x, &cities[n].y) == 2)
        n++;

    if (n <= 1) {
        printf("0.00\n");
        return 0;
    }

    // Generate identity permutation
    int next[11];
    for (int i = 0; i < n; i++)
        next[i] = i;

    float min_len = INFINITY;

    // Helper: compute current path length
    #define compute_length() ({ \
        float len = 0; \
        for (int i = 0; i < n; i++) \
            len += distance(cities[next[i]], cities[next[(i+1)%n]]); \
        len; \
    })

    // Heap's algorithm to generate all permutations
    int i = 0;
    int stack[11] = {0};

    while (i < n) {
        if (stack[i] < i) {
            int j = (i % 2) ? stack[i] : 0;
            int tmp = next[i]; next[i] = next[j]; next[j] = tmp;
            stack[i]++;
            i = 0;
        } else {
            stack[i++] = 0;
            float len = compute_length();
            if (len < min_len)
                min_len = len;
        }
    }

    printf("%.2f\n", min_len);
    return 0;
}