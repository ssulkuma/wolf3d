/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:55:17 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/06/30 11:31:34 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"

# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600

# define ESC_KEY 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126

typedef struct s_mlx
{
	void	*connection;
	void	*window;
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_mlx;

typedef struct s_position
{
	double	x;
	double	y;
}			t_position;

void	error(const char *str);
int		key_events(int key_code, t_mlx *mlx);
int		close_window_event(t_mlx *mlx);
#endif
