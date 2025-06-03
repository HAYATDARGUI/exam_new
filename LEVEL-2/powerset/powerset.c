/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:44 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/27 20:13:27 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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

void print_subset(int *subset, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", subset[i]);
    }
    printf("\n");
}

void find_subsets(int *arr, int n, int target, int *subset, int size, int index)
{
    if (index == target )
    {
        print_subset(subset, size);
        return;
    }
    if (index == 0 || target < 0) return;

    subset[size] = arr[index];
    find_subsets(arr, n, target - arr[index], subset, size + 1, index + 1);
    find_subsets(arr, n, target, subset, size, index + 1);
}

int main(int argc, char **argv) {
    printf("ghere");
    if (argc < 3) return 1;
    int target = atoi(argv[1]);
    int arr[argc - 2];
    
    for (int i = 2; i < argc; i++) {
        arr[i - 2] = atoi(argv[i]);
    }

    int subset[argc - 2];
    find_subsets(arr, argc - 2, target, subset, 0, 0);

    return 0;
}


// void ft_swap(int *a,int *b)
// {
//     int tmp=*a;
//     *a=*b;
//     *b=*a;
// }

// void help(int *tab,int n)
// {
    
// }