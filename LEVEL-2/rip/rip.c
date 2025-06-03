/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:12 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/20 18:53:07 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    print_solved(char *str) {
    for (int i = 0; str[i]; i++)
        write (1, str + i, 1);
    write(1, "\n", 1);
}

void solve(char *str, int pos, int open, int min_rem, char *tmp, int tmp_pos) {
    if (!str[pos]) {
        if (open == 0 && min_rem == 0) {
            tmp[tmp_pos] = 0;
            print_solved(tmp);
        }
        return;
    }
    if (min_rem > 0) {
        tmp[tmp_pos] = ' ';
        solve(str, pos + 1, open, min_rem - 1, tmp, tmp_pos + 1);
    }
    if (str[pos] == '(') {
        tmp[tmp_pos] = '(';
        solve(str, pos + 1, open + 1, min_rem, tmp, tmp_pos + 1);
    }
    else if (str[pos] == ')') {
        if (open > 0)
        {
            tmp[tmp_pos] = ')';
            solve(str, pos + 1, open - 1, min_rem, tmp, tmp_pos + 1);
        }
    }
    else {
        tmp[tmp_pos] = str[pos];
        solve(str, pos + 1, open, min_rem, tmp, tmp_pos + 1);
    }
    return;
}

int    get_min_removals(char *str) {
    int open = 0, close = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close++;
        }
        i++;
    }
    return (open + close);
}

int main(int ac, char **av) {
    if (ac != 2)
        return 1;
    int i = 0;
    while (av[1][i])
        i++;
    char tmp[i + 1];
    int min_rem = get_min_removals(av[1]);
    solve(av[1], 0, 0, min_rem, tmp, 0);
}