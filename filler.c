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
	ft_putnbr_fd(xy->y, 1);
	write(1, " ", 1);
	ft_putnbr_fd(xy->x, 1);
	write(1, "\n", 1);
}

// static void			output_fd(t_dot *xy)
// {
// 	dprintf(fd, "*** On the standart output: ***|\n");
// 	ft_putnbr_fd(xy->x, fd);
// 	write(fd, " ", 1);
// 	ft_putnbr_fd(xy->y, fd);
// 	write(fd, "\n", 1);
// }

static short int	get_num_str(char *line)
{
	while (*line && !ft_isdigit(*line))
		line++;
	if (!(*line))
		return (0);
	return (ft_atoi(line));
}

static void			free_job(short int **map, short int lines, t_dot *coords)
{
	int		i;

	i = -1;
	while (++i < lines)
		free(map[i]);
	free(coords);
}

void				fill_grid()
{
	t_grid	*field;
	t_piece	*piece;
	t_dot	*res;
	char	*line;

	field = (t_grid *)malloc(sizeof(t_grid));
	piece = (t_piece *)malloc(sizeof(t_piece));
	get_next_line(0, &line);
	field->player_num = get_num_str(line);
	free(line);
	//fd = open("file.txt", O_CREAT | O_RDWR | O_TRUNC);//////////
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, "Plateau", 7) == 0)
			get_grid(field, line);
		get_piece(piece);
		res = find_dot(field, piece);
		free_job(field->grid, field->y, piece->coords);
		free(line);
		//output_fd(res);
		output(res);
	}
}
