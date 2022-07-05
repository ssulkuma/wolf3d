/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:55:17 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/05 14:02:29 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"

# include <stdio.h>
# include <fcntl.h>
# include <string.h>

# define WIDTH 800
# define HEIGHT 600
# define BUFFER_SIZE 10

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

typedef struct s_map
{
	int		width;
	int		height;
	int		**matrix;
}			t_map;

typedef struct s_position
{
	double	x;
	double	y;
}			t_position;

void	error(const char *str);
void	buff_error(char *saved_map, int file);
void	matrix_error(char **matrix, char *saved_map, int index);
void	read_map(char *map_file, t_map *map);
int		key_events(int key_code, t_mlx *mlx);
int		mouse_events(int button, int x, int y, t_mlx *mlx);
int		close_window_event(t_mlx *mlx);

#endif
