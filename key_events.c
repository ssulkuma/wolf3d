/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:20:18 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/15 13:52:24 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Key event to move backwards inside the map.*/

static void	backward_movement_key(t_mlx *mlx)
{
	int		next_backward_x;
	int		next_backward_y;

	next_backward_x = (int)(mlx->player->position.x - mlx->player->direction.x
			* mlx->player->move_speed);
	next_backward_y = (int)(mlx->player->position.y - mlx->player->direction.y
			* mlx->player->move_speed);
	if (!mlx->map->matrix[next_backward_x][(int)mlx->player->position.y])
		mlx->player->position.x -= mlx->player->direction.x
			* mlx->player->move_speed;
	if (!mlx->map->matrix[(int)mlx->player->position.x][next_backward_y])
		mlx->player->position.y -= mlx->player->direction.y
			* mlx->player->move_speed;
	ft_bzero(mlx->address, (WIDTH * HEIGHT * 4));
	create_threads(mlx, mlx->map, mlx->player);
}

/*Key event to move forward inside the map.*/

static void	forward_movement_key(t_mlx *mlx)
{
	int		next_forward_x;
	int		next_forward_y;

	next_forward_x = (int)(mlx->player->move_speed * mlx->player->direction.x
			+ mlx->player->position.x);
	next_forward_y = (int)(mlx->player->move_speed * mlx->player->direction.y
			+ mlx->player->position.y);
	if (!mlx->map->matrix[next_forward_x][(int)mlx->player->position.y])
		mlx->player->position.x += mlx->player->direction.x
			* mlx->player->move_speed;
	if (!mlx->map->matrix[(int)mlx->player->position.x][next_forward_y])
		mlx->player->position.y += mlx->player->direction.y
			* mlx->player->move_speed;
	ft_bzero(mlx->address, (WIDTH * HEIGHT * 4));
	create_threads(mlx, mlx->map, mlx->player);
}

/*Function to be called when any key down related events are triggered. ESC key
 * destroys the created image and window, before exiting properly.*/

int	key_events(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(mlx->connection, mlx->image);
		mlx_destroy_window(mlx->connection, mlx->window);
		exit(0);
	}
	if (keycode == ARROW_DOWN)
		backward_movement_key(mlx);
	if (keycode == ARROW_UP)
		forward_movement_key(mlx);
	return (0);
}
