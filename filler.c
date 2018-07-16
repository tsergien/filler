/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 10:48:26 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/07 10:48:28 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

static void			output(t_dot *xy)
{
	dprintf(g_fd, "output: %d %d\n", xy->y, xy->x);
	ft_putnbr_fd(xy->y, 1);
	write(1, " ", 1);
	ft_putnbr_fd(xy->x, 1);
	write(1, "\n", 1);
}

static short int	get_num_str(char *line)
{
	while (*line && !ft_isdigit(*line))
		line++;
	if (!(*line))
		return (0);
	return (ft_atoi(line));
}

static void			free_job(short int **map,
					short int lines, t_dot *coords, char got_map)
{
	int		i;

	i = -1;
	if (got_map)
	{
		while (++i < lines)
			free(map[i]);
	}
	free(coords);
}

void				fill_grid(void)
{
	t_grid	*field;
	t_piece	*piece;
	t_dot	*res;
	char	*line;
	char	got_map;

	field = (t_grid *)malloc(sizeof(t_grid));
	piece = (t_piece *)malloc(sizeof(t_piece));
	get_next_line(0, &line);
	field->player_num = get_num_str(line);
	free(line);
	while (get_next_line(0, &line) > 0)
	{
		got_map = 0;
		if (ft_strncmp(line, "Plat", 4) == 0)
		{
			got_map = 1;
			get_grid(field, line);
		}
		get_piece(piece);
		res = find_dot(field, piece);
		free_job(field->grid, field->y, piece->coords, got_map);
		free(line);
		output(res);
	}
}
