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
	field->grid[x][y] = x + y + 1;
	while (++i < field->y)
	{
		j = -1;
		while (++j < field->x)
		{
			if (field->grid[i][j] == -op_num && (ABS(x - j) + ABS(y - i)) < field->grid[x][y])
				field->grid[x][y] = ABS(x - j) + ABS(y - i);
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
			if (field->grid[i][j] == -field->player_num)
				fill_min_dist(i, j, field);
		}
	}
}

static t_dot	*coord_min_dist(t_grid *field)
{
	int		i;
	int		j;
	int		min;
	t_dot	*res;

	res = (t_dot *)malloc(sizeof(t_dot));
	min = field->x + field->y + 1;
	i = -1;
	while (++i < field->y)
	{
		j = -1;
		while (++j < field->x)
		{
			if (field->grid[i][j] >= 0 && field->grid[i][j] < min)
			{
				min = field->grid[i][j];
				res->x = j;
				res->y = i;
			}
		}
	}
	return (res);
}

static t_dot	*insert_piece(t_grid *field, t_piece *piece)
{
	t_dot	*opt_coord;

	opt_coord = coord_min_dist(field);
	if (insertable(piece, opt_coord->x, opt_coord->y, field))
		return (opt_coord);
	field->grid[opt_coord->x][opt_coord->y] = -field->player_num;
	if (is_end_game(piece, field))
	{
		opt_coord->x = 0;
		opt_coord->y = 0;
		return (opt_coord);
	}
	return (insert_piece(field, piece));
}

t_dot			*find_dot(t_grid *field, t_piece *piece)
{
	fill_distances(field);
	dprintf(3, "DIST***************\n\n");//
	print_map_dist(field->grid, field->x, field->y);//
	return (insert_piece(field, piece));
}
