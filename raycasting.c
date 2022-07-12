/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:09:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/12 12:59:42 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	values(t_vector *player, t_vector *direction, t_vector *cam_plane)
{
	player->x = 12;
	player->y = 12;
	direction->x = -1;
	direction->y = 0;
	cam_plane->x = 0;
	cam_plane->y = 0.66;
}	

void raycasting(t_mlx *mlx, int x, int y)
{
	//int			y;
	//int			x;
	double      cam_position;
	t_vector    player;
	t_vector    direction;
	t_vector    cam_plane;
	t_ray       ray;

	values(&player, &direction, &cam_plane);
	//x = 0;
	//while (x < WIDTH)
	//{
		cam_position = 2.0 * x / (double)WIDTH - 1.0;
		ray.direction.x = direction.x + cam_plane.x * cam_position;
		ray.direction.y = direction.y + cam_plane.y * cam_position;
		mlx->map->x = player.x;
		mlx->map->y = player.y;
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
			ray.grid.x = (player.x - mlx->map->x) * ray.delta.x;
		}
		else
		{
			ray.step.x = 1;
			ray.grid.x = (mlx->map->x + 1 - player.x) * ray.delta.x;
		}
		if (ray.direction.y < 0)
		{
			ray.step.y = -1;
			ray.grid.y = (player.y - mlx->map->y) * ray.delta.y;
		}
		else
		{
			ray.step.y = 1;
			ray.grid.y = (mlx->map->y + 1.0 - player.y) * ray.delta.y;
		}
		while (!ray.wall)
		{
			if (ray.grid.x < ray.grid.y)
			{
				ray.grid.x += ray.delta.x;
				mlx->map->x += ray.step.x;
				ray.wall_side = 0;
			}
			else
			{
				ray.grid.y += ray.delta.y;
				mlx->map->y += ray.step.y;
				ray.wall_side = 1;
			}
			if (mlx->map->matrix[mlx->map->x][mlx->map->y] > 0)
				ray.wall = 1;
		}
		if (ray.wall_side == 0)
			ray.length = ray.grid.x - ray.delta.x;
		else
			ray.length = ray.grid.y - ray.delta.y;
		ray.wall_height = (int)(HEIGHT / ray.length);
		mlx->map->wall_start = -ray.wall_height / 2 + HEIGHT / 2;
		if (mlx->map->wall_start < 0)
			mlx->map->wall_start = 0;
		mlx->map->wall_end = ray.wall_height / 2 + HEIGHT / 2;
		if (mlx->map->wall_end >= HEIGHT)
			mlx->map->wall_end = HEIGHT - 1;
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
			if (mlx->map->matrix[mlx->map->x][mlx->map->y] == 1)
				draw_pixel_to_image(mlx, x, y, 0x3A243B);
			else if (mlx->map->matrix[mlx->map->x][mlx->map->y] == 2)
				draw_pixel_to_image(mlx, x, y, 0xD1768F);
			else if (mlx->map->matrix[mlx->map->x][mlx->map->y] == 3)
				draw_pixel_to_image(mlx, x, y, 0xED820E);
			else if (mlx->map->matrix[mlx->map->x][mlx->map->y] == 4)
				draw_pixel_to_image(mlx, x, y, 0xFFE8E9);
			y++;
		}
		//x++;
	//}
	//mlx_put_image_to_window(mlx->connection, mlx->window, mlx->image, 0, 0);
}
