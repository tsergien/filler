/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 18:00:40 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/06 18:00:42 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

static void		fill_min_dist(short int x, short int y, t_grid *field)
{
	short int		op_num;
	short int		i;
	short int		j;
	
	op_num = (field->player_num == 1 ? 2 : 1);
	i = -1;
	field->grid[y][x] = field->x + field->y + 1;
	while (++i < field->y)
	{
		j = -1;
		while (++j < field->x)
		{
			if (field->grid[i][j] == -op_num && (ft_abs(x - j) + ft_abs(y - i)) < field->grid[y][x])
				field->grid[y][x] = ft_abs(j - x) + ft_abs(i - y);
		}
	}
}

static void		fill_distances(t_grid *field)
{
	int		i;
	int		j;

	i = -1;
	while (++i < field->y)
	{
		j = -1;
		while (++j < field->x)
		{
			if (field->grid[i][j] == 0)
				fill_min_dist(j, i, field);
		}
	}
}

t_dot			*find_dot(t_grid *field, t_piece *piece)
{
	fill_distances(field);
	return (find_spot(piece, field));
}

void			bzero_coords(t_dot *s, int n)
{
	t_dot	*ptr;

	ptr = s;
	while (n--)
	{
		set_dot(ptr, -1, -1);
		ptr++;
	}
}
