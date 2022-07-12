/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:09:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/12 15:33:40 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void raycasting(t_data *data, int x, int y)
{
	double      cam_position;
	int			map_x;
	int			map_y;
	t_ray       ray;

	//x = 0;
	//while (x < WIDTH)
	//{
		cam_position = 2.0 * x / (double)WIDTH - 1.0;
		ray.direction.x = data->player->direction.x + data->player->cam_plane.x * cam_position;
		ray.direction.y = data->player->direction.y + data->player->cam_plane.y * cam_position;
		map_x = data->player->position.x;
		map_y = data->player->position.y;
		if (ray.direction.x == 0)
			ray.direction.x = 1e30;
		if(ray.direction.y == 0)
			ray.direction.y = 1e30;
		ray.delta.x = ft_fabs(1.0 / ray.direction.x);
		ray.delta.y = ft_fabs(1.0 / ray.direction.y);
		ray.wall = 0;
		if (ray.direction.x < 0)
		{
			ray.step.x = -1;
			ray.grid.x = (data->player->position.x - map_x) * ray.delta.x;
		}
		else
		{
			ray.step.x = 1;
			ray.grid.x = (map_x + 1 - data->player->position.x) * ray.delta.x;
		}
		if (ray.direction.y < 0)
		{
			ray.step.y = -1;
			ray.grid.y = (data->player->position.y - map_y) * ray.delta.y;
		}
		else
		{
			ray.step.y = 1;
			ray.grid.y = (map_y + 1.0 - data->player->position.y) * ray.delta.y;
		}
		while (!ray.wall)
		{
			if (ray.grid.x < ray.grid.y)
			{
				ray.grid.x += ray.delta.x;
				map_x += ray.step.x;
				ray.wall_side = 0;
			}
			else
			{
				ray.grid.y += ray.delta.y;
				map_y += ray.step.y;
				ray.wall_side = 1;
			}
			if (data->map->matrix[map_x][map_y] > 0)
				ray.wall = 1;
		}
		if (ray.wall_side == 0)
			ray.length = ray.grid.x - ray.delta.x;
		else
			ray.length = ray.grid.y - ray.delta.y;
		ray.wall_height = (int)(HEIGHT / ray.length);
		data->map->wall_start = -ray.wall_height / 2 + HEIGHT / 2;
		if (data->map->wall_start < 0)
			data->map->wall_start = 0;
		data->map->wall_end = ray.wall_height / 2 + HEIGHT / 2;
		if (data->map->wall_end >= HEIGHT)
			data->map->wall_end = HEIGHT - 1;
		printf("X %d\n", x);
		printf("CAM POS %f\n", cam_position);
		printf("RAY DIR X %f\n", ray.direction.x);
		printf("RAY DIR Y %f\n", ray.direction.y);
		printf("RAY DELTA X %f\n", ray.delta.x);
		printf("RAY DELTA Y %f\n", ray.delta.y);
		printf("RAY STEP X %f\n", ray.step.x);
		printf("RAY STEP Y %f\n", ray.step.y);
		printf("RAY LENGHT %f\n", ray.length);
		printf("RAY WALL HEIGHT %d\n", ray.wall_height);
		printf("\n");
		y = 0;
		while (y < ray.wall_height)
		{
			if (data->map->matrix[map_x][map_y] == 1)
				draw_pixel_to_image(data->mlx, x, y, 0x3A243B);
			else if (data->map->matrix[map_x][map_y] == 2)
				draw_pixel_to_image(data->mlx, x, y, 0xD1768F);
			else if (data->map->matrix[map_x][map_y] == 3)
				draw_pixel_to_image(data->mlx, x, y, 0xED820E);
			else if (data->map->matrix[map_x][map_y] == 4)
				draw_pixel_to_image(data->mlx, x, y, 0xFFE8E9);
			y++;
		}
		//x++;
	//}
	//mlx_put_image_to_window(mlx->connection, mlx->window, mlx->image, 0, 0);
}
