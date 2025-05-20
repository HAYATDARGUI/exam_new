/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:44 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/20 13:28:09 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>

// int simple_atoi(char *str) {
//     int result = 0;
//     int sign = 1;
//     if (*str == '-') {
//         sign = -1;
//         str++;
//     }

//     while (*str) {
//         result = result * 10 + (*str - '0');
//         str++;
//     }

//     return result * sign;
// }

// void print_subset(int *subset, int size) {
//     for (int i = 0; i < size; i++) {
//         printf("%d ", subset[i]);
//     }
//     printf("\n");
// }

// void find_subsets(int *arr, int n, int target, int *subset, int size, int index) {
//     if (target == 0) {
//         print_subset(subset, size);
//         return;
//     }
//     if (index == n || target < 0) return;

//     subset[size] = arr[index];
//     find_subsets(arr, n, target - arr[index], subset, size + 1, index + 1);
//     find_subsets(arr, n, target, subset, size, index + 1);
// }

// int main(int argc, char **argv) {
//     if (argc < 3) return 1;

//     int target = simple_atoi(argv[1]);
//     int arr[argc - 2];
    
//     for (int i = 2; i < argc; i++) {
//         arr[i - 2] = simple_atoi(argv[i]);
//     }

//     int subset[argc - 2];
//     find_subsets(arr, argc - 2, target, subset, 0, 0);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


void process(int *tab, int *res, int target, int res_i, int start, int total, int n, int *flag) {
    if (total == target && res_i > 0) {
        for (int i = 0; i < res_i; i++) {
            printf("%d%s", res[i], i < res_i - 1 ? " " : "\n");
        }
        *flag = 1;
    }

    for (int i = start; i < n; i++) {
        if (i > start && tab[i] == tab[i - 1]) continue; 
        if (total + tab[i] > target) break;           

        res[res_i] = tab[i];
        process(tab, res, target, res_i + 1, i + 1, total + tab[i], n, flag);
    }
}

int main(int ac, char **av) {
    if (ac < 3) {
        printf("\n");
        return 0;
    }

    int target = atoi(av[1]);
    int n = ac - 2;
    int *tab = malloc(n * sizeof(int));
    int *res = malloc(n * sizeof(int));
    int flag = 0;

    for (int i = 0; i < n; i++)
        tab[i] = atoi(av[i + 2]);

    sort(tab, n); 
    if (target == 0)
    {
        printf("\n");
        flag = 1;
    }
    process(tab, res, target, 0, 0, 0, n, &flag);

    if (!flag)
        printf("\n");

    free(tab);
    free(res);
    return 0;
}