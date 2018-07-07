/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 18:41:35 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/05 18:42:06 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

static void	get_xy(t_grid *field)
{
	char	*line;

	get_next_line(0, &line);
	while (*line && !ft_isdigit(*line))
		line++;
	field->y = ft_atoi(line);
	dprintf(3, "y: %d\n", field->y);/////
	while (ft_isdigit(*line))
		line++;
	while (*line && !ft_isdigit(*line))
		line++;
	field->x = ft_atoi(line);
	dprintf(3, "x: %d\n", field->x);/////
}

void		set_line(char *line, short int *array)
{
	int		i;

	i = 0;
	while (*line)
	{
		if (*line == '.')
			array[i++] = 0;
		else if (*line == 'X')
			array[i++] = 2;
		else if (*line == 'O')
			array[i++] = 1;
		else if (*line == 'o')
			array[i++] = -1;
		else if (*line == 'x')
			array[i++] = -2;
		line++;
	}
}

short int	get_num_str(char *line)
{
	while (*line && !ft_isdigit(*line))
		line++;
	if (!(*line))
		return (0);
	return (ft_atoi(line));
}

void		get_grid()
{
	char	*line;
	int		fd;
	t_grid	field;
	int		i;

	i = -1;
	fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC);//del later.or not
	get_next_line(0, &line);
	field.player_num = get_num_str(line);
	get_xy(&field);
	get_next_line(0, &line);
	field.grid = (short int **)malloc(sizeof(short int *) * (field.y + 1));
	while (++i < field.y)
	{
		get_next_line(0, &line);
		field.grid[i] = (short int *)malloc(sizeof(short int) * (field.x + 1));
		set_line(line + 4, field.grid[i]);
	}
	print_map(field.grid, field.x, field.y);
	free(line);
}