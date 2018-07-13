/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inserting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 12:28:45 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/13 12:28:48 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

static int		dist_sum(short int **map, t_piece *tok, short int x, short int y)
{
	int		sum;
	t_dot	*ptr;

	ptr = tok->coords;
	sum = 0;
	while (ptr->x != -1)
	{
		sum += map[y + ptr->y][x + ptr->x];
		ptr++;
	}
	return (sum);
}

static int		insertable(t_piece *tok, short int x, short int y, t_grid *map)
{
	short int	overlap;
	short int	op_num;
	t_dot		*ptr_coords;

	ptr_coords = tok->coords;
	overlap = 0;
	op_num = map->player_num % 2 + 1;
	while (ptr_coords->x != -1)
	{
		if (map->grid[y + ptr_coords->y][x + ptr_coords->x] == -map->player_num)
			overlap++;
		if (map->grid[y + ptr_coords->y][x + ptr_coords->x]
		 == -op_num || overlap > 1)
			return (0);
		ptr_coords++;
	}
	if (overlap == 0)
		return (0);
	return (1);
}

t_dot		*find_spot(t_piece *piece, t_grid *field)
{
	int			dist;
	int			i;
	int			j;
	t_dot		*opt;
	int			new_dist;
	
	opt = (t_dot *)malloc(sizeof(t_dot));
	i = -1;
	dist = field->x + field->y + 1;
	set_dot(opt, 0, 0);
	while (++i < field->y - piece->rows + 1)
	{
		j = -1;
		while (++j < field->x - piece->cols + 1)
		{
			if (insertable(piece, j, i, field))
			{
				new_dist = dist_sum(field->grid, piece, j, i);
				if (new_dist < dist)
				{
					dist = new_dist;
					set_dot(opt, j - piece->min.x, i - piece->min.y);
				}
			}
		}
	}
	return (opt);
}
