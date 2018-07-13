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
	char	*ptr;

	get_next_line(0, &line);
	ptr = line;
	while (*line && !ft_isdigit(*line))
		line++;
	*y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line && !ft_isdigit(*line))
		line++;
	*x = ft_atoi(line);
	free(ptr);
}

void	normalize(t_piece *tok)
{
	t_dot	*p;
	
	p = tok->coords;
	set_dot(&tok->min, tok->cols, tok->rows);
	while (p->x != -1)
	{
		if (p->x < tok->min.x)
			tok->min.x = p->x;
		if (p->y < tok->min.y)
			tok->min.y = p->y;
		p++;
	}
	p = tok->coords;
	while (p->x != -1)
	{
		p->x -= tok->min.x;
		p->y -= tok->min.y;
		p++;
	}
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
	normalize(piece);
	free_matrix(tok, piece->rows);
}
