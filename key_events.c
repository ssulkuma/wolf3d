/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:20:18 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/13 14:29:24 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Key event to rotate the view right. Both player direction and camera plane
 * must be moved in union.*/

static void	rotate_right(t_mlx *mlx)
{
	double	previous_direction_x;
	double	previous_cam_plane_x;

	previous_direction_x = mlx->player->direction.x;
	mlx->player->direction.x = mlx->player->direction.x
		* cos(-mlx->player->turn_speed) - mlx->player->direction.y
		* sin(-mlx->player->turn_speed);
	mlx->player->direction.y = previous_direction_x
		* sin(-mlx->player->turn_speed) + mlx->player->direction.y
		* cos(-mlx->player->turn_speed);
	previous_cam_plane_x = mlx->player->cam_plane.x;
	mlx->player->cam_plane.x = mlx->player->cam_plane.x
		* cos(-mlx->player->turn_speed) - mlx->player->cam_plane.y
		* sin(-mlx->player->turn_speed);
	mlx->player->cam_plane.y = previous_cam_plane_x
		* sin(-mlx->player->turn_speed) + mlx->player->cam_plane.y
		* cos(-mlx->player->turn_speed);
	ft_bzero(mlx->image->address, (WIDTH * HEIGHT * 4));
	render(mlx);
}

/*Key event to rotate the view left. Both player direction and camera plane
 * must be moved in union.*/

static void	rotate_left(t_mlx *mlx)
{
	double	previous_direction_x;
	double	previous_cam_plane_x;

	previous_direction_x = mlx->player->direction.x;
	mlx->player->direction.x = mlx->player->direction.x
		* cos(mlx->player->turn_speed) - mlx->player->direction.y
		* sin(mlx->player->turn_speed);
	mlx->player->direction.y = previous_direction_x
		* sin(mlx->player->turn_speed) + mlx->player->direction.y
		* cos(mlx->player->turn_speed);
	previous_cam_plane_x = mlx->player->cam_plane.x;
	mlx->player->cam_plane.x = mlx->player->cam_plane.x
		* cos(mlx->player->turn_speed) - mlx->player->cam_plane.y
		* sin(mlx->player->turn_speed);
	mlx->player->cam_plane.y = previous_cam_plane_x
		* sin(mlx->player->turn_speed) + mlx->player->cam_plane.y
		* cos(mlx->player->turn_speed);
	ft_bzero(mlx->image->address, (WIDTH * HEIGHT * 4));
	render(mlx);
}

/*Key event to move backwards inside the map. Calculates the next x and y
 * position on the map based on the direction the player is heading.*/

static void	move_backwards(t_mlx *mlx)
{
	double		next_x;
	double		next_y;

	next_x = mlx->player->position.x - mlx->player->direction.x
		* mlx->player->move_speed;
	next_y = mlx->player->position.y - mlx->player->direction.y
		* mlx->player->move_speed;
	if (next_x < 0.0 || next_x >= mlx->map->width
		|| next_y < 0.0 || next_y >= mlx->map->height)
		return ;
	if (mlx->map->matrix[(int)next_x][(int)mlx->player->position.y] != 1)
		mlx->player->position.x -= mlx->player->direction.x
			* mlx->player->move_speed;
	if (mlx->map->matrix[(int)mlx->player->position.x][(int)next_y] != 1)
		mlx->player->position.y -= mlx->player->direction.y
			* mlx->player->move_speed;
	ft_bzero(mlx->image->address, (WIDTH * HEIGHT * 4));
	render(mlx);
}

/*Key event to move forward inside the map. Calculates the next x and y
 * position on the map based on the direction the player is heading.*/

static void	move_forward(t_mlx *mlx)
{
	double		next_x;
	double		next_y;

	next_x = mlx->player->position.x + mlx->player->direction.x
		* mlx->player->move_speed;
	next_y = mlx->player->position.y + mlx->player->direction.y
		* mlx->player->move_speed;
	if (next_x < 0.0 || next_x >= mlx->map->width
		| next_y < 0.0 || next_y >= mlx->map->height)
		return ;
	if (mlx->map->matrix[(int)next_x][(int)mlx->player->position.y] != 1)
		mlx->player->position.x += mlx->player->direction.x
			* mlx->player->move_speed;
	if (mlx->map->matrix[(int)mlx->player->position.x][(int)next_y] != 1)
		mlx->player->position.y += mlx->player->direction.y
			* mlx->player->move_speed;
	ft_bzero(mlx->image->address, (WIDTH * HEIGHT * 4));
	render(mlx);
}

/*Function to be called when any key down related events are triggered. ESC key
 * destroys the created image and window, before exiting properly.*/

int	key_events(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(mlx->connection, mlx->image->image);
		mlx_destroy_window(mlx->connection, mlx->window);
		exit(0);
	}
	if (keycode == M_KEY)
	{
		if (mlx->menu)
			mlx->menu = 0;
		else
			mlx->menu = 1;
	}
	if (keycode == ARROW_RIGHT)
		rotate_right(mlx);
	if (keycode == ARROW_LEFT)
		rotate_left(mlx);
	if (keycode == ARROW_DOWN)
		move_backwards(mlx);
	if (keycode == ARROW_UP)
		move_forward(mlx);
	return (0);
}
