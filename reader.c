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

void	get_xy(t_grid *field, int fd)
{
	char	*line;

	get_next_line(0, &line);
	while (*line && !ft_isdigit(*line))
		line++;
	field->y = ft_atoi(line);
	dprintf(fd, "y: %d\n", field->y);//
	while (ft_isdigit(*line))
		line++;
	while (*line && !ft_isdigit(*line))
		line++;
	field->x = ft_atoi(line);
	dprintf(fd, "x: %d\n", field->x);// 
}

void	increase(char **map)
{

}

void	get_grid()
{
	char	*line;
	int		fd;
	t_grid	field;
	int		i;

	i = 0;
	fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC);
	//get player number (O-1 X-2) and save it somewhere
	get_next_line(0, &line);//  $$$ exec p1 : [./giena.filler] 
	get_xy(&field, fd);
	get_next_line(fd, &line);// 01234567890123... line
	field.grid = (short int **)malloc(sizeof(short int *) * (x + 1));
	while (i < )
	{
		get_next_line(0, &line);
		dprintf(fd, "%s\n", line);//
		field.grid[i] = (short int *)malloc(sizeof(short int) * ( y + 1));
		field.grid[i++] = line;
	}
}