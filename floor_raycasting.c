/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:00:47 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/22 16:25:00 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Calculates the leftmost and rightmost ray directions.*/

static void	utmost_rays(t_data *data, t_floor *floor)
{
	floor->left_ray.x = data->player->direction.x - data->player->cam_plane.x;
	floor->left_ray.y = data->player->direction.y - data->player->cam_plane.y;
	floor->right_ray.x = data->player->direction.x + data->player->cam_plane.x;
	floor->right_ray.y = data->player->direction.y + data->player->cam_plane.y;
}

/*Calculates the scale the texture needs to be drawn in and loops through 
 * the x-axis colorig the corresponding pixel of the coordinate.*/

static void	draw_floor(t_data *data, t_image *texture, t_floor *floor, int y)
{
	double		tex_x;
	double		tex_y;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		tex_x = (int)(TEX_WIDTH * (floor->position.x - (int)floor->position.x))
			& (TEX_WIDTH - 1);
		tex_y = (int)(TEX_HEIGHT * (floor->position.y - (int)floor->position.y))
			& (TEX_HEIGHT - 1);
		floor->color = get_pixel_from_image(&texture[4], tex_x, tex_y);
		draw_pixel_to_image(data->mlx, x, y, floor->color);
		floor->position.x += floor->step.x;
		floor->position.y += floor->step.y;
		x++;
	}
}

/*The floor raycasting function. Instead of drawing the lines vertically like
 * in the walls, the floor is drawn horizontally. Counts where the player's
 * view hits the horizontal line and the position the ray is hitting on the
 * map.*/

void	*floor_raycasting(void *thread)
{
	t_data		*data;
	t_floor		floor;
	int			y;

	data = (t_data *)thread;
	y = data->start_y + 320;
	while (y < data->end_y + 320)
	{
		utmost_rays(data, &floor);
		floor.horizon = y - HEIGHT / 2;
		floor.step.x = (HEIGHT / 2 / floor.horizon)
			* (floor.right_ray.x - floor.left_ray.x) / WIDTH;
		floor.step.y = (HEIGHT / 2 / floor.horizon)
			* (floor.right_ray.y - floor.left_ray.y) / WIDTH;
		floor.position.x = data->player->position.x
			+ (HEIGHT / 2 / floor.horizon) * floor.left_ray.x;
		floor.position.y = data->player->position.y
			+ (HEIGHT / 2 / floor.horizon) * floor.left_ray.y;
		draw_floor(data, data->mlx->texture, &floor, y);
		y++;
	}
	pthread_exit(NULL);
}
