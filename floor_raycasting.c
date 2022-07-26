/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:00:47 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/26 15:35:38 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	floor_raycasting(t_data *data, t_image *texture)
{
	t_floor		floor;
	int			y;
	int			x;
	int			tex_y;
	int			tex_x;
	int			color;

	y = 0;
	while (y < HEIGHT)
	{
		floor.left_ray.x = data->player->position.x - data->player->cam_plane.x;
		floor.left_ray.y = data->player->position.y - data->player->cam_plane.y;
		floor.right_ray.x = data->player->position.x + data->player->cam_plane.x;
		floor.right_ray.y = data->player->position.y + data->player->cam_plane.y;
		
		floor.horizon = y - HEIGHT / 2;
		floor.step.x = (HEIGHT / 2 / floor.horizon) * (floor.left_ray.x - floor.right_ray.x) / WIDTH;
		floor.step.y = (HEIGHT / 2 / floor.horizon) * (floor.left_ray.y - floor.right_ray.y) / WIDTH;

		floor.position.x = data->player->position.x + (HEIGHT / 2) * floor.left_ray.x;
		floor.position.y = data->player->position.y + (HEIGHT / 2) * floor.left_ray.y;
		x = 0;
		while (x < WIDTH)
		{
			floor.map_x = (int)floor.position.x;
			floor.map_y = (int)floor.position.y;
			tex_x = (int)(TEX_WIDTH * (floor.position.x - floor.map_x)) & 63;
			tex_y = (int)(TEX_HEIGHT * (floor.position.y - floor.map_x)) & 63;
			floor.position.x += floor.step.x;
			floor.position.y += floor.step.y;
			color = get_pixel_from_image(&texture[1], tex_x, tex_y);
			draw_pixel_to_image(data->mlx, x, y, color);
			x++;
		}
		y++;
	}
}
