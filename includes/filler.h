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
	char		launch;
}				t_grid;

typedef struct	s_piece
{
	short int	rows;
	short int	cols;
	t_dot		*coords;
}				t_piece;

/***************FILLER******************/
void	fill_grid();
t_dot	*find_dot(t_grid *field, t_piece *piece);

/***************READING*****************/
void	get_grid(t_grid *field);
void	get_xy(short int *x, short int *y);

/****************MAP********************/
void	print_map(short int **map, short int x, short int y);//
void	print_coords(t_dot *coords);
void	print_dot(t_dot *xy);

void	print_map_dist(short int **map, short int x, short int y);//

/****************DISTANCE**************/
void	fill_min_dist(short int x, short int y, t_grid *field);
t_dot	*find_spot(t_piece *piece, t_grid *field);

/****************PIECE******************/
void	get_piece(t_piece *piece);
int		is_end_game(t_piece *piece, t_grid *field);
int		insertable(t_piece *piece, short int x, short int y, t_grid *field);
void	bzero_coords(t_dot *s, int n);
void	set_dot(t_dot *xy, short int x, short int y);

#endif
