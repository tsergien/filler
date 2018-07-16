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

static void		insert_cur_dist(t_grid *field, int cur_dist, int op_num)
{
	int		i;
	int		j;

	i = -1;
	while (++i < field->y)
	{
		j = -1;
		while (j++ < field->x)
		{
			if (field->grid[i][j] == field->x + field->y + 2)
			{
				if ((i - 1 > 0 && field->grid[i - 1][j] == -op_num) ||
				(i + 1 < field->y && field->grid[i + 1][j] == -op_num) ||
				(j - 1 > 0 && field->grid[i][j - 1] == -op_num) || (j + 1
				< field->x && field->grid[i][j + 1] == -op_num))
					field->grid[i][j] = 1;
				if ((i - 1 > 0 && field->grid[i - 1][j] == cur_dist - 1) ||
				(i + 1 < field->y && field->grid[i + 1][j] == cur_dist - 1) ||
				(j - 1 > 0 && field->grid[i][j - 1] == cur_dist) || (j + 1 <
				field->x && field->grid[i][j + 1] == cur_dist - 1))
					field->grid[i][j] = cur_dist;
			}
		}
	}
}

static void		dist_around(t_grid *field)
{
	int		cur_dist;
	int		op_num;

	op_num = field->player_num % 2 + 1;
	cur_dist = 1;
	while (cur_dist < field->x + field->y)
	{
		insert_cur_dist(field, cur_dist, op_num);
		cur_dist++;
	}
}

t_dot			*find_dot(t_grid *field, t_piece *piece)
{
	print_map_dist(field->grid, field->x, field->y);
	dist_around(field);
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

/*
**static void		fill_min_dist(short int x, short int y, t_grid *field)
**{
**	short int		op_num;
**	short int		i;
**	short int		j;
**
**	op_num = (field->player_num == 1 ? 2 : 1);
**	i = -1;
**	field->grid[y][x] = field->x + field->y + 1;
**	while (++i < field->y)
**	{
**		j = -1;
**		while (++j < field->x)
**		{
**			if (field->grid[i][j] == -op_num && (ft_abs(x - j)
**			+ ft_abs(y - i)) < field->grid[y][x])
**				field->grid[y][x] = ft_abs(j - x) + ft_abs(i - y);
**		}
**	}
**}
**
**static void		fill_distances(t_grid *field)
**{
**	int		i;
**	int		j;
**
**	i = -1;
**	while (++i < field->y)
**	{
**		j = -1;
**		while (++j < field->x)
**		{
**			if (field->grid[i][j] == 0)
**				fill_min_dist(j, i, field);
**		}
**	}
**}
*/
