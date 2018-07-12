/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 09:36:46 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/07 09:36:47 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

static char	get_symbol(short int cell)
{
	if (cell == 0)
		return ('.');
	if (cell == 1)
		return ('O');
	if (cell == 2)
		return ('X');
	if (cell == -1)
		return ('o');
	return ('x');
}

void	print_dot(t_dot *xy)
{
	dprintf(3, "x: %d, y: %d\n", xy->x, xy->y);
}

void	print_map(short int **map, short int x, short int y)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	while (i < y)
	{
		write(3, "***-> ", 6);
		j = 0;
		while (j < x)
		{
			temp = get_symbol(map[i][j]);
			write(3, &temp, 1);
			j++;
		}
		write(3, "\n", 1);
		i++;
	}
}

void	print_map_dist(short int **map, short int x, short int y)
{
	int		i;
	int		j;

	i = 0;
	write(3, "          *** DISTANCE MAP ***\n", 31);
	while (i < y)
	{
		write(3, "***-> ", 6);
		j = 0;
		while (j < x)
		{
			dprintf(3, "%3d|", map[i][j]);
			j++;
		}
		dprintf(3, "\n");
		i++;
	}
}

void	print_coords(t_dot *coords)
{
	t_dot *p;

	p = coords;
	while (p->x != -1)
	{
		dprintf(3, "p->x: %d, p->y: %d\n", p->x, p->y);
		p++;
	}
}