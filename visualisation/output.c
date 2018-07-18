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

int			output_mlx(t_params *par)
{
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr,
		7, 3, 0xc6c6c6, "Press escape to exit");
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr,
		370, 30, BLUE, par->names->player1);
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr,
		WIN_WIDTH / 2 - 20, 30, WHITE, "vs");
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr, WIN_WIDTH - 470,
	30, PINK, par->names->player2);
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

int			deal_space(int key, t_params *par)
{
	if (key == 32)
		return (output_mlx(par));
	return (0);
}

void		win(t_params *par, char *line)
{
	char	*ptr;
	int		res1;
	int		res2;

	ptr = line;
	while (!ft_isdigit(*ptr))
		ptr++;
	res1 = ft_atoi(ptr);
	mlx_string_put(par->p->mlx_ptr, par->p->win_ptr,
		370, 50, BLUE, ft_itoa(res1));
	if (get_next_line(0, &line) > 0)
	{
		ptr = line;
		while (!ft_isdigit(*ptr))
			ptr++;
		res2 = ft_atoi(ptr);
		mlx_string_put(par->p->mlx_ptr, par->p->win_ptr,
			WIN_WIDTH - 470, 50, PINK, ft_itoa(res2));
		free(line);
	}
}

int			visualise(t_params *par)
{
	char	*line;
	int		ret;

	ret = get_next_line(0, &line);
	if (ret > 0 && ft_strncmp("Plat", line, 4) == 0)
	{
		mlx_clear_window(par->p->mlx_ptr, par->p->win_ptr);
		get_map(par->map, line);
		output_mlx(par);
		free_map(par->map->grid, par->map->y);
		free(line);
	}
	else if (ret > 0 && ft_strncmp("== ", line, 3) == 0)
	{
		win(par, line);
		free(line);
	}
	return (0);
}
