/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 18:43:18 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/05 18:44:38 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <stdio.h>//

typedef struct	s_dot
{
	short int	x;
	short int	y;
}				t_dot;

typedef struct	s_grid
{
	short int	**grid;
	short int	x;
	short int	y;
	short int	player_num;
}				t_grid;

typedef struct	s_piece
{
	short int	rows;
	short int	cols;
	t_dot		*coords;
}				t_piece;

/***************FILLER******************/
void	fill();
/***************READING*****************/
void	get_grid(t_grid *field);

/****************MAP********************/
void	print_map(short int **map, short int x, short int y);

/****************PIECE******************/
void	get_piece(t_piece *piece);

#endif
