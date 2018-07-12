/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:25:11 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/07 12:25:12 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

/*
** check all piece coordinates on map         **
** remember that distances are already filled ** 
*/

static int		dist_sum(short int **map, t_piece *tok, short int x, short int y)
{
	int		sum;
	t_dot	*ptr;

	ptr = tok->coords;
	sum = 0;
	while (ptr->x != -1)
	{
		sum += map[y + ptr->y][x + ptr->x];
		ptr++;
	}
	return (sum);
}

static int		insertable(t_piece *tok, short int x, short int y, t_grid *map)
{
	short int	overlap;
	short int	op_num;
	t_dot		*ptr_coords;

	ptr_coords = tok->coords;
	overlap = 0;
	op_num = (map->player_num == 1 ? 2 : 1);
	while (ptr_coords->x != -1)
	{
		if (map->grid[y + ptr_coords->y][x + ptr_coords->x] == -map->player_num)
			overlap++;
		if (map->grid[y + ptr_coords->y][x + ptr_coords->x]
		 == -op_num || overlap > 1)
			return (0);
		ptr_coords++;
	}
	if (overlap == 0)
		return (0);
	return (1);
}

t_dot		*find_spot(t_piece *piece, t_grid *field)
{
	int			dist;
	int			i;
	int			j;
	t_dot		*opt;
	int			new_dist;
	
	opt = (t_dot *)malloc(sizeof(t_dot));
	i = -1;
	dist = field->x + field->y + 1;
	set_dot(opt, 0, 0);
	while (++i < field->y - piece->rows + 1)
	{
		j = -1;
		while (++j < field->x - piece->cols + 1)
		{
			if (insertable(piece, j, i, field))
			{
				new_dist = dist_sum(field->grid, piece, j, i);
				if (new_dist < dist)
				{
					dist = new_dist;
					set_dot(opt, j, i);
				}
			}
		}
	}
	return (opt);
}

short int	get_char_token(char **tok, short int lines)
{
	short int	ast;
	short int	i;
	short int	j;

	i = -1;
	ast = 0;
	while (++i < lines)
	{
		get_next_line(0, &tok[i]);
		j = 0;
		while (tok[i][j])
		{
			if (tok[i][j++] == '*')
				ast++;
		}
	}
	return (ast);
}

static void	get_xy_piece(short int *x, short int *y)
{
	char	*line;

	get_next_line(0, &line);
	while (*line && !ft_isdigit(*line))
		line++;
	*y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line && !ft_isdigit(*line))
		line++;
	*x = ft_atoi(line);
}

void	get_piece(t_piece *piece)
{
	char		**tok;
	int			i;
	int			j;
	t_dot		*ptr_coord;
	short int	ast;

	get_xy_piece(&piece->cols, &piece->rows);
	tok = (char **)malloc(sizeof(char *) * piece->rows);
	ast = get_char_token(tok, piece->rows);
	piece->coords = (t_dot *)malloc(sizeof(t_dot) * (ast + 1));
	bzero_coords(piece->coords, ast + 1);
	i = -1;
	ptr_coord = piece->coords;
	while (++i < piece->rows)
	{
		j = -1;
		while (tok[i][++j])
		{
			if (tok[i][j] == '*')
				set_dot(ptr_coord++, j, i);
		}
	}
	set_dot(ptr_coord, -1, -1);
	free_matrix(tok, piece->rows);
}
