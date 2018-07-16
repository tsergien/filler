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

void		normalize(t_piece *tok)
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
	dprintf(g_fd, "min.x = %d, min.y = %d\n", tok->min.x, tok->min.y);
	if (!(tok->min.x == 0 && tok->min.y == 0))
	{
		while (p->x != -1)
		{
			p->x -= tok->min.x;
			p->y -= tok->min.y;
			p++;
		}
	}
}

void		set_max_xy(t_piece *tok)
{
	t_dot	*p;

	p = tok->coords;
	tok->max.x = 0;
	tok->max.y = 0;
	while (p->x != -1)
	{
		if (p->x > tok->max.x)
			tok->max.x = p->x;
		if (p->y > tok->max.y)
			tok->max.y = p->y;
		p++;
	}
	dprintf(g_fd, "max.x = %d, max.y = %d\n", tok->max.x, tok->max.y);
}

void		get_piece(t_piece *piece)
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
	set_max_xy(piece);
	normalize(piece);
	free_matrix(tok, piece->rows);
}
