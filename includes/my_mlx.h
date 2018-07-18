/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 09:32:36 by tsergien          #+#    #+#             */
/*   Updated: 2018/07/18 09:32:39 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX
#define MY_MLX
# include "filler.h"
# include "../libft/includes/libft.h"
# include "mlx.h"
# define WIN_HEIGHT 1200
# define WIN_WIDTH 1000
# define C_EMPTY 0x8b8d8e
# define BLUE 0x4595ad
# define LIGHT_BLUE 0xa6cded
# define PINK 0x96365f
# define LIGHT_PINK 0xe59ebc
# define WHITE 0xffffff


int fd;///////////////////////

typedef struct  s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_mlx;

typedef struct  s_names
{
    char    *player1;
    char    *player2;
}               t_names;

typedef struct  s_params
{
    t_mlx   *p;
    t_grid  *map;
    t_names *names;
}               t_params;

void            visualise(t_mlx *p);
void	        put_field(t_mlx *p, t_grid *map);
void			get_map(t_grid *field, char *line);
void			get_players(t_grid *map, t_names *names);

#endif
