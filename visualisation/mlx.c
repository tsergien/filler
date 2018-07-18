/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:50:52 by tsergien          #+#    #+#             */
/*   Updated: 2018/06/21 20:07:11 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/my_mlx.h"
#include <stdio.h>///

char			*get_name(char *line)
{
	char	*start;
	char	*end;
	char	*name;

	start = ft_strchr(line, '/');
	start++;
	end = start;
	while (*end && ft_isalpha(*end))
		end++;
	name = ft_strsub(start, 0, end - start);
	dprintf(fd, "player_name: %s\n", name);
	return (name);
}

void			get_players(t_grid *map, t_names *names)
{
	char	*line;
	char	*start;
	char	*end;
	char	flag;

	flag = 0;
	while (flag < 2 && get_next_line(0, &line) > 0)
	{
		dprintf(fd, "line : %s\n", line);
		if (ft_strstr(line, "exec"))
		{
			flag++;
			if (flag == 1)
				names->player1 = get_name(line);
			else
				names->player2 = get_name(line);
		}
		free(line);
	}
}

static void		set_line(char *line, short int *array)
{
	int		i;

	i = 0;
	while (*line)
	{
		if (*line == '.')
			array[i++] = 0;
		else if (*line == 'X')
			array[i++] = -2;
		else if (*line == 'O')
			array[i++] = -1;
		else if (*line == 'x')
			array[i++] = -4;
		else if (*line == 'o')
			array[i++] = -3;
		line++;
	}
}

static int      deal_key(int key, void *param)
{
	if (key == 53)
		exit(1);
	return (0);
}

static int      exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void			get_map(t_grid *field, char *line)
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
		set_line(line + 4, field->grid[i]);
		free(line);
	}
}

int				main(void)
{
	t_mlx	*p;

	fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY);//
	p = (t_mlx *)malloc(sizeof(t_mlx));
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Filler");
	visualise(p);
	mlx_hook(p->win_ptr, 2, 5, deal_key, (void *)0);
	mlx_hook(p->win_ptr, 17, 1L << 17, exit_x, (void *)0);
	mlx_loop(p->mlx_ptr);
	return (0);
}
