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

void		get_xy(short int *x, short int *y, char *line)
{
	while (*line && !ft_isdigit(*line))
		line++;
	*y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line && !ft_isdigit(*line))
		line++;
	*x = ft_atoi(line);
}

void		set_line(char *line, short int *array)
{
	int		i;

	i = 0;
	while (*line)
	{
		if (*line == '.')
			array[i++] = 0;
		else if (*line == 'X' || *line == 'x')
			array[i++] = -2;
		else if (*line == 'O' || *line == 'o')
			array[i++] = -1;
		line++;
	}
}

void		get_grid(t_grid *field, char *line)
{
	int		i;

	i = -1;
	get_xy(&(field->x), &(field->y), line);
	get_next_line(0, &line);
	free(line);
	field->grid = (short int **)malloc(sizeof(short int *) * (field->y));
	while (++i < field->y)
	{
		get_next_line(0, &line);
		field->grid[i] = (short int *)malloc(sizeof(short int) * (field->x));
		ft_bzero(field->grid[i], field->x);
		set_line(line + 4, field->grid[i]);
		free(line);
	}
}

void		set_dot(t_dot *xy, short int x, short int y)
{
	xy->x = x;
	xy->y = y;
}

void		free_matrix(char **m, int lines)
{
	int		i;

	i = -1;
	while (++i < lines)
		free(m[i]);
}
