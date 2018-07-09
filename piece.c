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

int		insertable(t_piece *piece, short int x, short int y, t_grid *field)
{
	int			overlap;
	short int	op_num;
	
	overlap = 0;
	op_num = (field->player_num == 1 ? 2 : 1);
	while (piece->coords->x != -1)
	{
		if (field->grid[x + piece->coords->x][y + piece->coords->y] == -field->player_num
			|| field->grid[x + piece->coords->x][y + piece->coords->y] > 0)
			overlap++;
		if (field->grid[x + piece->coords->x][y + piece->coords->y]
		 == -op_num || overlap > 1)
			return (0);
		piece->coords++;
	}
	if (overlap == 0)
		return (0);
	return (1);
}

int		is_end_game(t_piece *piece, t_grid *field)
{
	int		i;
	int		j;

	i = -1;
	while (++i < field->y)
	{
		j = -1;
		while (++j < field->x)
		{
			if (insertable(piece, j, i, field))
				return (0);
		}
	}
	return (1);
}

void	get_piece(t_piece *piece)
{
	char	*line;
	int		i;
	int		j;

	get_xy(&piece->cols, &piece->rows);
	piece->coords = (t_dot *)malloc(sizeof(t_dot) * (piece->rows * piece->cols + 1));
	i = -1;
	dprintf(3, "rows: %d\n", piece->rows);//
	while (++i < piece->rows)
	{
		get_next_line(0, &line);
		j = 0;
		while (*(line + j))
		{
			dprintf(3, "line: %s\n", line);//
			if (*(line + j) == '*')
			{
				piece->coords->x = j;
				piece->coords->y = i;
				dprintf(3, "coords->x: %d\n", piece->coords->x);//
			 	dprintf(3, "coords->y: %d\n", piece->coords->y);//
				piece->coords++;
			}
			j++;
		}
	}
	piece->coords->x = -1;
	piece->coords->y = -1;
	free(line);
}
