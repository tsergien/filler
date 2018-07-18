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
	return (name);
}

void			get_players(t_names *names)
{
	char	*line;
	char	flag;

	flag = 0;
	while (flag < 2 && get_next_line(0, &line) > 0)
	{
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

void			set_line(char *line, short int *array)
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

static int		exit_x(void)
{
	exit(1);
	return (0);
}

int				main(void)
{
	t_params	*par;

	par = (t_params *)malloc(sizeof(t_params));
	par->p = (t_mlx *)malloc(sizeof(t_mlx));
	par->names = (t_names *)malloc(sizeof(t_names));
	par->map = (t_grid *)malloc(sizeof(t_grid));
	get_players(par->names);
	par->p->mlx_ptr = mlx_init();
	par->p->win_ptr = mlx_new_window(par->p->mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT, "Filler");
	mlx_loop_hook(par->p->mlx_ptr, visualise, par);
	mlx_hook(par->p->win_ptr, 17, 0, exit_x, (void *)0);
	mlx_loop(par->p->mlx_ptr);
	return (0);
}
