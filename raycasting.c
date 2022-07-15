/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:09:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/15 10:15:55 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Calculates the length that the ray has to move for 1 grid step in both the
x-axis or the y-axis. As well as the step within the starting grid to reach
first x-side or y-side. Ray.step will be used later to determine which grid
position on the map we're going move next, following the ray direction.*/

static void	ray_steps(t_data *data, t_ray *ray)
{
	ray->delta.x = ft_fabs(1.0 / ray->direction.x);
	ray->delta.y = ft_fabs(1.0 / ray->direction.y);
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->grid.x = (data->player->position.x - ray->map_x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->grid.x = (ray->map_x + 1 - data->player->position.x)
			* ray->delta.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->grid.y = (data->player->position.y - ray->map_y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->grid.y = (ray->map_y + 1.0 - data->player->position.y)
			* ray->delta.y;
	}
}

/*The digital differential analysis algorithm to calculate if there's a hit
to a wall in grid. Checks for every grid line on ray's way so the calculations
are minimized wihtout going past a possible wall. Calculates the full length of
the ray in the end.*/

static void	dda_algorithm(t_data *data, t_ray *ray)
{
	ray->wall.hit = 0;
	while (!ray->wall.hit)
	{
		if (ray->grid.x < ray->grid.y)
		{
			ray->grid.x += ray->delta.x;
			ray->map_x += ray->step.x;
			ray->wall.side = 0;
		}
		else
		{
			ray->grid.y += ray->delta.y;
			ray->map_y += ray->step.y;
			ray->wall.side = 1;
		}
		if (data->map->matrix[ray->map_x][ray->map_y] > 0)
			ray->wall.hit = 1;
	}
	if (ray->wall.side == 0)
		ray->length = ray->grid.x - ray->delta.x;
	else
		ray->length = ray->grid.y - ray->delta.y;
}

/*Determines the wall height for every x-coordinate.*/

static void	wall_heights(t_ray *ray)
{
	ray->wall.height = (int)(HEIGHT / ray->length);
	ray->wall.start = -ray->wall.height / 2 + HEIGHT / 2;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.height / 2 + HEIGHT / 2;
	if (ray->wall.end >= HEIGHT)
		ray->wall.end = HEIGHT - 1;
}

/*Draws the walls by looping through wall height.*/

static void	draw_walls(t_data *data, t_ray *ray, int x)
{
	int			y;

	y = ray->wall.start;
	while (y < ray->wall.end)
	{
		if (data->map->matrix[ray->map_x][ray->map_y] == 1)
			draw_pixel_to_image(data->mlx, x, y, 0x3A243B);
		else if (data->map->matrix[ray->map_x][ray->map_y] == 2)
			draw_pixel_to_image(data->mlx, x, y, 0xD1768F);
		else if (data->map->matrix[ray->map_x][ray->map_y] == 3)
			draw_pixel_to_image(data->mlx, x, y, 0xED820E);
		else if (data->map->matrix[ray->map_x][ray->map_y] == 4)
			draw_pixel_to_image(data->mlx, x, y, 0xFFE8E9);
		y++;
	}
}

/*This is where our raycasting begins. Cam_position represents what side
of the screen we're at on the x-axis. -1 is the left side, 0 center and 1
is the right side. Knowing this we can calculate the direction where the
ray is being cast.*/

void	raycasting(t_data *data, int x)
{
	double		cam_position;
	t_ray		ray;

	cam_position = 2.0 * x / (double)WIDTH - 1.0;
	ray.direction.x = data->player->direction.x
		+ data->player->cam_plane.x * cam_position;
	ray.direction.y = data->player->direction.y
		+ data->player->cam_plane.y * cam_position;
	ray.map_x = data->player->position.x;
	ray.map_y = data->player->position.y;
	if (ray.direction.x == 0)
		ray.direction.x = 1e30;
	if (ray.direction.y == 0)
		ray.direction.y = 1e30;
	ray_steps(data, &ray);
	dda_algorithm(data, &ray);
	wall_heights(&ray);
	printf("X %d\n", x);
	printf("CAM POS %f\n", cam_position);
	printf("RAY DIR X %f\n", ray.direction.x);
	printf("RAY DIR Y %f\n", ray.direction.y);
	printf("RAY DELTA X %f\n", ray.delta.x);
	printf("RAY DELTA Y %f\n", ray.delta.y);
	printf("RAY STEP X %f\n", ray.step.x);
	printf("RAY STEP Y %f\n", ray.step.y);
	printf("RAY LENGHT %f\n", ray.length);
	printf("RAY WALL HEIGHT %d\n", ray.wall.height);
	printf("\n");
	draw_walls(data, &ray, x);
}
