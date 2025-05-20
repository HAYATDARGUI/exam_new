/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:12 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/20 16:30:44 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_balanced(char *s) {
    int count = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') count++;
        if (s[i] == ')') count--;
        if (count < 0) return 0; 
    }
    return count == 0;  
}

void print_string(char *s) {
    for (int i = 0; s[i]; i++) {
        write(1, &s[i], 1);
    }
    write(1, "\n", 1);
}

void generate_combinations(char *s, int i, int open, int close) {
    if (!s[i]) {  
        if (is_balanced(s)) print_string(s);
        return;
    }

    char temp = s[i];


    if ((temp == '(' && open) || (temp == ')' && close)) {
        s[i] = ' '; 
        generate_combinations(s, i + 1, open - (temp == '('), close - (temp == ')'));
        s[i] = temp;  
    }

  
    generate_combinations(s, i + 1, open, close);
}

int main(int ac, char **av) {
    if (ac != 2) return 1; 

    int open = 0, close = 0;

    for (int i = 0; av[1][i]; i++) {
        if (av[1][i] == '(') open++;
        if (av[1][i] == ')') (open ? open-- : close++);
    }

    generate_combinations(av[1], 0, open, close); 
    return 0;
}
