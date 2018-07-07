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

void	get_piece(t_piece *piece)
{
	char	*line;
	int		i;
	int		j;

	get_next_line(0, &line);
	get_xy(piece->cols, piece->rows);
	i = 0;
	//how much memory do i need??? for coords
	while (get_next_line(0, &line) > 0)
	{
		j = 0;
		while (*line)
		{
			if (*line == '*')
				//set coords x = j, y = i
			j++;
		}
	}
}
