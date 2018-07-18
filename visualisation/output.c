/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 12:37:58 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/18 12:38:01 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/my_mlx.h"
#include <stdio.h>

int     output_mlx(t_params *par)
{
    mlx_clear_window(par->p->mlx_ptr, par->p->win_ptr);
    mlx_string_put(par->p->mlx_ptr, par->p->win_ptr, 10, 10, 0xc6c6c6, "Press escape to exit");
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr, 370, 20, BLUE, par->names->player1);
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr, WIN_WIDTH / 2 - 20, 20, WHITE, "vs");
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr, WIN_WIDTH - 470,
    20, PINK, par->names->player2);
    put_field(par->p, par->map);
	return (1);
}

void		free_map(short int **map, int lines)
{
	int		i;

	i = -1;
	while (++i < lines)
		free(map[i]);
}

void            visualise(t_mlx *p)
{
	char		*line;
	t_grid		*map;
	t_names		*names;
	t_params	*params;

	params = (t_params *)malloc(sizeof(t_params));
	names = (t_names *)malloc(sizeof(t_names));
	map = (t_grid *)malloc(sizeof(t_grid));
	get_players(map, names);
	params->p = p;
	params->names = names;
	while (get_next_line(0, &line))
	{
		if (ft_strncmp("Plat", line, 4) == 0)
		{
			params->map = map;
			get_map(map, line);
			dprintf(3, "here\n");
			mlx_loop_hook(p, output_mlx, params);
			free_map(map->grid, map->y);
			//output_mlx(p, map, names);
		}
		free(line);
	}
}
