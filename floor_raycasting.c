/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:00:47 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/27 13:12:10 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	floor_raycasting(t_data *data, t_image *texture)
{
	t_floor		floor;
	int			tex_y;
	int			tex_x;
	int			y;
	int			x;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		floor.left_ray.x = data->player->direction.x - data->player->cam_plane.x;
		floor.left_ray.y = data->player->direction.y - data->player->cam_plane.y;
		floor.right_ray.x = data->player->direction.x + data->player->cam_plane.x;
		floor.right_ray.y = data->player->direction.y + data->player->cam_plane.y;
		printf("FLOOR\n");
		printf("LEFT X %f\n", floor.left_ray.x);
		printf("RIGHT X %f\n", floor.right_ray.x);
		printf("LEFT Y %f\n", floor.left_ray.y);
		printf("RIGHT Y %f\n", floor.right_ray.y);
		floor.horizon = y - HEIGHT / 2;
		floor.step.x = (HEIGHT / 2 / floor.horizon) * (floor.right_ray.x - floor.left_ray.x) / WIDTH;
		floor.step.y = (HEIGHT / 2 / floor.horizon) * (floor.right_ray.y - floor.left_ray.y) / WIDTH;
		floor.position.x = data->player->position.x + (HEIGHT / 2 / floor.horizon) * floor.left_ray.x;
		floor.position.y = data->player->position.y + (HEIGHT / 2 / floor.horizon) * floor.left_ray.y;
		printf("STEP X %f\n", floor.step.x);
		printf("STEP Y %f\n", floor.step.y);
		printf("HORIZON %f\n", floor.horizon);
		printf("POS X %f\n", floor.position.x);
		printf("POS Y %f\n\n", floor.position.y);
		x = 0;
		while (x < WIDTH)
		{
			floor.map_x = (int)floor.position.x;
			floor.map_y = (int)floor.position.y;
			tex_x = (int)(TEX_WIDTH * (floor.position.x - floor.map_x));
			tex_y = (int)(TEX_HEIGHT * (floor.position.y - floor.map_y));
			floor.color = get_pixel_from_image(&texture[4], tex_x, tex_y);
			draw_pixel_to_image(data->mlx, x, y, floor.color);
			floor.position.x += floor.step.x;
			floor.position.y += floor.step.y;
			x++;
		}
		y++;
	}
}
