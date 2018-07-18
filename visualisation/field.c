/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:03:22 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/18 14:03:24 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/my_mlx.h"

static void     put_square(t_mlx *p, t_dot coords, int size, int color)
{
	int		i;
	int		j;

	i = coords.y;
	while (i < coords.y + size)
	{
		j = coords.x;
		while (j < coords.x + size)
		{
			mlx_pixel_put(p->mlx_ptr, p->win_ptr, j, i, color);
			j++;
		}
		i++;
	}
}

static int      get_color(short int cell)
{
    if (cell == -1)
        return (BLUE);
    else if (cell == -3)
        return (LIGHT_BLUE);
    if (cell == -2)
        return (PINK);
    else if (cell == -4)
        return (LIGHT_PINK);
    return (C_EMPTY);
}

void            put_field(t_mlx *p, t_grid *map)
{
    t_dot   ij;
    t_dot   coords;
	int		skape;
	int		start_i;
	int		start_j;

	skape = (WIN_WIDTH - WIN_WIDTH / 5) / map->x;
	start_j = (WIN_WIDTH - map->x * (skape - 2) - 2 * (map->x - 1)) / 2;
	start_i = WIN_HEIGHT / 13;
	ij.y = -1;
	while (++ij.y < map->y)
	{
		ij.x = -1;
		while (++ij.x < map->x)
        {
            coords.x = start_j + ij.x * skape + 2;
            coords.y = start_i + ij.y * skape + 2;
            put_square(p, coords, skape - 3, get_color(map->grid[ij.y][ij.x]));
        }
	}
}