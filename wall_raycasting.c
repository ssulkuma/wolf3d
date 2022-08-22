/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:09:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/22 16:30:57 by ssulkuma         ###   ########.fr       */
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
are minimized without going past a possible wall. Calculates which compass
point on of a wall block we've hit.*/

static int	dda_algorithm(t_data *data, t_ray *ray)
{
	if (ray->grid.x < ray->grid.y)
	{
		ray->grid.x += ray->delta.x;
		ray->map_x += ray->step.x;
		if (data->player->position.x > ray->map_x)
			ray->wall.side = 0;
		else
			ray->wall.side = 1;
	}
	else
	{
		ray->grid.y += ray->delta.y;
		ray->map_y += ray->step.y;
		if (data->player->position.y > ray->map_y)
			ray->wall.side = 2;
		else
			ray->wall.side = 3;
	}
	if (ray->map_x < 0 || ray->map_x >= data->map->width
		|| ray->map_y < 0 || ray->map_y >= data->map->height)
		return (-1);
	if (data->map->matrix[ray->map_x][ray->map_y] == 1)
		return (1);
	return (0);
}

/*Calculates the perpendicular distance instead the Euclidean distance of the
 * ray hit to get rid of the fisheye effect. Determines the wall height for
 * every x-coordinate and the position the ray hit the wall.*/

static void	wall_heights(t_ray *ray, t_data *data)
{
	if (ray->wall.hit == -1)
		return ;
	if (ray->wall.side == 0 || ray->wall.side == 1)
		ray->length = ray->grid.x - ray->delta.x;
	else
		ray->length = ray->grid.y - ray->delta.y;
	ray->wall.height = (int)(HEIGHT / ray->length);
	ray->wall.start = -ray->wall.height / 2 + HEIGHT / 2;
	ray->wall.end = ray->wall.height / 2 + HEIGHT / 2;
	if (ray->wall.side == 0 || ray->wall.side == 1)
		ray->hit = data->player->position.y + ray->length * ray->direction.y;
	else
		ray->hit = data->player->position.x + ray->length * ray->direction.x;
	ray->hit -= floor(ray->hit);
}

/*Calculates the scale of the texture needs to be drawn in and loops through
 * the wall height of the y-axis. Saves distance to wall for every x coordinate
 * that will be used later to draw objects.*/

static void	draw_walls(t_data *data, t_ray *ray, int x, t_image *texture)
{
	int			y;
	int			color;
	double		step;
	double		tex_y;
	double		tex_x;

	if (ray->wall.hit == -1)
		return ;
	step = 1.0 * TEX_HEIGHT / ray->wall.height;
	tex_y = 0;
	tex_x = (int)(ray->hit * TEX_WIDTH);
	if ((ray->wall.side == 0 || ray->wall.side == 1) && ray->direction.x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if ((ray->wall.side == 2 || ray->wall.side == 3) && ray->direction.y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	y = ray->wall.start;
	while (y < ray->wall.end)
	{
		color = get_pixel_from_image(&texture[ray->wall.side], tex_x, tex_y);
		draw_pixel_to_image(data->mlx, x, y, color);
		tex_y += step;
		y++;
	}
	data->depth[x] = ray->length;
}

/*This is where our raycasting begins. Cam_position represents what side
of the screen we're at on the x-axis. -1 is the left side, 0 center and 1
is the right side. Knowing this we can calculate the direction where the
ray is being cast.*/

void	draw_wall_raycasting(t_data *data, int x, t_image *texture)
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
	ray_steps(data, &ray);
	ray.wall.hit = 0;
	while (!ray.wall.hit)
		ray.wall.hit = dda_algorithm(data, &ray);
	wall_heights(&ray, data);
	draw_walls(data, &ray, x, texture);
}
