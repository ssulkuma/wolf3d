/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:55:17 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/24 16:03:48 by ssulkuma         ###   ########.fr       */
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
# define HEIGHT 640
# define BUFFER_SIZE 10
# define THREADS 10
# define ANIMATION_DURATION 50
# define MAX_OBJECTS 50
# define PI 3.141592654

# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define SKYBOX_TEX_WIDTH 800
# define SKYBOX_TEX_HEIGHT 200
# define MAX_TEXTURES 12
# define TEX_0 "./textures/00.xpm"
# define TEX_1 "./textures/01.xpm"
# define TEX_2 "./textures/02.xpm"
# define TEX_3 "./textures/03.xpm"
# define TEX_4 "./textures/04.xpm"
# define TEX_5 "./textures/05.xpm"
# define TEX_6 "./textures/05.xpm"
# define TEX_7 "./textures/07.xpm"
# define TEX_8 "./textures/08.xpm"
# define TEX_9 "./textures/barrel.xpm"
# define TEX_10 "./textures/10.xpm"
# define TEX_11 "./textures/11.xpm"

# define ESC_KEY 53
# define M_KEY 46
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MOUSE_LEFT 1

typedef struct s_map
{
	int			width;
	int			height;
	int			**matrix;
	int			object_count;
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
	double		move_speed;
	double		turn_speed;
}				t_player;

typedef struct s_image
{
	void		*image;
	char		*address;
	int			bits_per_pixel;
	int			len;
	int			endian;
}				t_image;

typedef struct s_mlx
{
	void		*connection;
	void		*window;
	t_image		*image;
	t_image		*texture;
	t_image		*skybox;
	t_map		*map;
	t_player	*player;
	t_vector	fire;
	t_vector	wand;
	double		fire_scale;
	double		depth[WIDTH];
	int			click;
	int			wand_done;
	int			menu;
}				t_mlx;

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
	double		hit;
	int			map_x;
	int			map_y;
}				t_ray;

typedef struct s_floor
{
	t_vector	left_ray;
	t_vector	right_ray;
	t_vector	position;
	t_vector	step;
	double		horizon;
	int			color;
}				t_floor;

typedef struct s_data
{
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
}				t_data;

typedef struct s_skybox
{
	t_vector	tex;
	t_vector	step;
	double		result;
	int			color;

}				t_skybox;

typedef struct s_object
{
	t_vector	position;
	t_vector	sprite;
	t_vector	transform;
	int			width;
	int			height;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			color;
}				t_object;

void	error(const char *str);
void	buff_error(char *saved_map, int file);
void	matrix_error(char **matrix, char *saved_map, int index);
void	read_map(char *map_file, t_map *map);
void	check_map_characters(char *saved_map);
void	check_map_size(char **matrix, t_map *map);
void	count_objects_in_map(char *saved_map, t_map *map);
void	get_textures(t_image *texture);
void	draw_pixel_to_image(t_mlx *mlx, int x, int y, int color);
void	render(t_mlx *mlx);
void	create_threads(t_mlx *mlx, void *(*function)(void *));
void	draw_wall_raycasting(t_data *mlx, int x, t_image *texture);
void	*floor_raycasting(void *thread);
void	*skybox(void *thread);
void	*objects(void *thread);
void	wand(t_mlx *mlx);
void	fire(t_mlx *mlx);
int		get_pixel_from_image(t_image *texture, int x, int y);
int		key_events(int key_code, t_mlx *mlx);
int		mouse_events(int button, int x, int y, t_mlx *mlx);
int		close_window_event(t_mlx *mlx);
int		spell_cast_animation(t_mlx *mlx);

#endif
