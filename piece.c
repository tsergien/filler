/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:25:11 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/07 12:25:12 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

/*
** check all piece coordinates on map         **
** remember that distances are already filled ** 
*/

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

int		insertable(t_piece *tok, short int x, short int y, t_grid *map)
{
	short int	overlap;
	short int	op_num;
	t_dot		*ptr_coords;

	ptr_coords = tok->coords;
	overlap = 0;
	op_num = (map->player_num == 1 ? 2 : 1);
	while (ptr_coords->x != -1)
	{
		if (y + ptr_coords->y > map->y || x + ptr_coords->x > map->x)
			return (0);
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
	while (++i < field->y)
	{
		j = -1;
		while (++j < field->x)
		{
			if (insertable(piece, j, i, field))
			{
				print_coords(piece->coords);
				dprintf(3, "insertable: j: %d, i: %d\n", j , i);/////////////
				new_dist = dist_sum(field->grid, piece, j, i);
				dprintf(3, "dist: %d\n", new_dist);///////////////////
				if (new_dist < dist)
				{
					dist = new_dist;
					set_dot(opt, j, i);
				}
				dprintf(3, "New opt: ");//////////////
				print_dot(opt);
			}
		}
	}
	return (opt);
}

void	get_piece(t_piece *piece)
{
	char	*line;
	int		i;
	int		j;
	t_dot	*ptr_coord;

	get_xy(&piece->cols, &piece->rows);
	piece->coords = (t_dot *)malloc(sizeof(t_dot) * (piece->rows * piece->cols + 1));
	bzero_coords(piece->coords, piece->rows * piece->cols + 1);
	i = -1;
	ptr_coord = piece->coords;
	while (++i < piece->rows)
	{
		get_next_line(0, &line);
		j = 0;
		while (*(line + j))
		{
			if (*(line + j) == '*')
			{
				ptr_coord->x = j;
				ptr_coord->y = i;
				//dprintf(3, "ptr_coord->x: %d\n", ptr_coord->x);//
			 	//dprintf(3, "ptr_coord->y: %d\n", ptr_coord->y);//
				ptr_coord++;
			}
			j++;
		}
	}
	ptr_coord->x = -1;
	ptr_coord->y = -1;
	print_coords(piece->coords);
	free(line);
}
