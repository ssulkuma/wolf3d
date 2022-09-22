/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:33:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/22 14:15:22 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*The digital differential analysis algorithm to calculate if there's a hit
 * to an  object in grid. Checks for every grid line on ray's way so the
 * calculations are minimized without going past a possible object. Checks
 * which object texture to use based on number in map.*/

static int	dda_algorithm(t_data *data, t_ray *ray, t_object *object)
{
	if (ray->grid.x < ray->grid.y)
	{
		ray->grid.x += ray->delta.x;
		ray->map_x += ray->step.x;
	}
	else
	{
		ray->grid.y += ray->delta.y;
		ray->map_y += ray->step.y;
	}
	if (ray->map_x < 0 || ray->map_x >= data->map->width
		|| ray->map_y < 0 || ray->map_y >= data->map->height)
		return (-1);
	if (data->map->matrix[ray->map_x][ray->map_y] == 2
		|| data->map->matrix[ray->map_x][ray->map_y] == 3
		|| data->map->matrix[ray->map_x][ray->map_y] == 4)
	{
		object->texture = data->map->matrix[ray->map_x][ray->map_y] + 4;
		return (1);
	}
	return (0);
}

/*Calculates the distance between player and object, the inverse camera
 * matrix for the object and the starting coordinates for the object.*/

static void	object_calculations(t_data *data, t_ray *ray, t_object *object)
{
	if ((ray->grid.x - ray->delta.x) > (ray->grid.y - ray->delta.y))
		ray->length = ray->grid.x - ray->delta.x;
	else
		ray->length = ray->grid.y - ray->delta.y;
	object->distance.x = object->position.x - data->player->position.x;
	object->distance.y = object->position.y - data->player->position.y;
	object->inverse = 1 / (data->player->cam_plane.x * data->player->direction.y
			- data->player->direction.x * data->player->cam_plane.y);
	object->transform.x = object->inverse * (data->player->direction.y
			* object->distance.x - data->player->direction.x
			* object->distance.y);
	object->transform.y = object->inverse * (-data->player->cam_plane.y
			* object->distance.x + data->player->cam_plane.x
			* object->distance.y);
	object->height = ft_abs((int)(HEIGHT / object->transform.y)) / 2;
	object->start_y = (-object->height / 2 + HEIGHT / 2)
		+ TEX_HEIGHT / object->transform.y;
	if (object->start_y < 0)
		object->start_y = 0;
	object->end_y = (object->height / 2 + HEIGHT / 2)
		+ TEX_HEIGHT / object->transform.y;
	if (object->end_y > HEIGHT - 1)
		object->end_y = HEIGHT - 1;
	object->start_x = (-object->height / 2) + ((int)(WIDTH / 2)
			*(1 + object->transform.x / object->transform.y));
}

/*Draws object if ray to object is shorter than to wall.*/

static void	draw_objects(t_data *data, int x, t_object *object, t_ray *ray)
{
	int			y;
	int			color;
	double		step;
	double		tex_y;
	double		tex_x;

	step = 1.0 * TEX_HEIGHT / object->height;
	tex_y = 0;
	tex_x = (x - object->start_x) * step;
	if (tex_x < 0 || tex_x > TEX_WIDTH)
		return ;
	y = object->start_y;
	while (y < object->end_y)
	{
		color = get_pixel_from_image(&data->mlx->texture[object->texture],
				tex_x, tex_y);
		if (color != 0x000000 && ray->length <= data->mlx->depth[x])
			draw_pixel_to_image(data->mlx, x, y, color);
		tex_y += step;
		y++;
	}
}

/*A recursive dda function to draw all the objects in an order from the
 * furthest to the closest.*/

static void	recursive_dda(t_data *data, t_ray *ray, int x)
{
	t_ray		current_ray;
	t_object	current_object;

	current_object.hit = 0;
	while (!current_object.hit)
		current_object.hit = dda_algorithm(data, ray, &current_object);
	ft_memcpy(&current_ray, ray, sizeof(t_ray));
	if (current_object.hit == 1)
	{
		current_object.position.x = ray->map_x + 0.5;
		current_object.position.y = ray->map_y + 0.5;
		recursive_dda(data, ray, x);
	}
	if (current_object.hit == -1)
		return ;
	object_calculations(data, &current_ray, &current_object);
	draw_objects(data, x, &current_object, &current_ray);
}

/*This is where our raycasting begins. Cam_position represents what side
 * of the screen we're at on the x-axis. -1 is the left side, 0 center and 1
 * is the right side. Knowing this we can calculate the direction where the
 * ray is being cast.*/

void	object_raycasting(t_data *data, int x)
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
	recursive_dda(data, &ray, x);
}
