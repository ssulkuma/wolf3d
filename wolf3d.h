/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:55:17 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/13 12:28:17 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>

# define WIDTH 800
# define HEIGHT 600
# define BUFFER_SIZE 10
# define THREADS 10

# define ESC_KEY 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126

typedef struct s_map
{
	int			width;
	int			height;
	int			**matrix;
}				t_map;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	t_vector	position;
	t_vector	direction;
	t_vector	cam_plane;
}				t_player;

typedef struct s_mlx
{
	void		*connection;
	void		*window;
	void		*image;
	char		*address;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_map		*map;
	t_player	*player;
}				t_mlx;

typedef struct s_thread
{
	int			start_x;
	int			end_x;
}				t_thread;

typedef struct s_wall
{
	int			hit;
	int			side;
	int			height;
	int			start;
	int			end;
}				t_wall;

typedef struct s_ray
{
	t_vector	direction;
	t_vector	step;
	t_vector	delta;
	t_vector	grid;
	t_wall		wall;
	double		length;
	int			map_x;
	int			map_y;
}				t_ray;

typedef struct s_data
{
	int			start_x;
	int			end_x;
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
	t_thread	*thread;
}				t_data;

void	error(const char *str);
void	buff_error(char *saved_map, int file);
void	matrix_error(char **matrix, char *saved_map, int index);
void	read_map(char *map_file, t_map *map);
void	check_map_characters(char *saved_map);
void	check_map_size(char **matrix, t_map *map);
void	draw_pixel_to_image(t_mlx *mlx, int x, int y, int color);
void	create_threads(t_mlx *mlx, t_map *map, t_player *player);
void	raycasting(t_data *mlx, int x);
int		key_events(int key_code, t_mlx *mlx);
int		mouse_events(int button, int x, int y, t_mlx *mlx);
int		close_window_event(t_mlx *mlx);

#endif
