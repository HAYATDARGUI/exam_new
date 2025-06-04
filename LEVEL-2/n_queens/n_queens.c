/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:11:59 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/04 14:20:00 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	help(int n, int c, int *b)
{
	int	safe;
	int	d;

	if (c == n)
	{
		for (int i = 0; i < n; i++)
			printf("%d%c", b[i], i < n - 1 ? ' ' : '\n');
		return ;
	}
	for (int r = 0; r < n; r++)
	{
		safe = 1;
		for (int i = 0; i < c; i++)
		{
			d = c - i;
			if (b[i] == r || b[i] == r - d || b[i] == r + d)
			{
				safe = 0;
				break ;
			}
		}
		if (safe)
		{
			b[c] = r;
			help(n, c + 1, b);
		}
	}
}

void	help2(int n)
{
	int	b[n];

	help(n, 0, b);
}

int	main(int arc, char **arv)
{
	if (arc != 2 || atoi(arv[1]) <= 0)
	{
		return (1);
	}
	help2(atoi(arv[1]));
}