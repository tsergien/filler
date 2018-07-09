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

void	output(t_dot *xy)
{
	char	tmp;

	tmp = '0' + xy->x;
	write(1, &tmp, 1);
	write(1, " ", 1);
	tmp = '0' + xy->y;
	write(1, &tmp, 1);
	write(1, "\n", 1);
}

void	fill_grid()
{
	t_grid	*field;
	t_piece	*piece;
	t_dot	*res;

	field = (t_grid *)malloc(sizeof(t_grid));
	piece = (t_piece *)malloc(sizeof(t_piece));
	get_grid(field);
	get_piece(piece);
	res = find_dot(field, piece);
	output(res);
}
