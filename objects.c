/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:33:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/29 16:26:27 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Checks how much the fire texture needs to be scaled for a specific frame.*/

static int	get_fire_scale(t_mlx *mlx)
{
	if (mlx->fire_scale < 5)
		return (1);
	else if (mlx->fire_scale >= 5 && mlx->fire_scale < 10)
		return (2);
	else if (mlx->fire_scale >= 10 && mlx->fire_scale < 15)
		return (3);
	else if (mlx->fire_scale >= 15 && mlx->fire_scale < 20)
		return (4);
	else
		return (5);
}

/*Draws the fire to the position of mouse click.*/

void	fire(t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;
	int		scale;

	if (mlx->click && mlx->wand_done)
	{
		scale = get_fire_scale(mlx);
		x = 0;
		while (x < TEX_WIDTH * scale)
		{
			y = 0;
			while (y < TEX_HEIGHT * scale)
			{
				color = get_pixel_from_image(&mlx->texture[11], x / scale,
						y / scale);
				if (color != 0x000000)
					draw_pixel_to_image(mlx, mlx->fire.x - (33 * scale) + x,
						mlx->fire.y - (45 * scale) + y, color);
				y++;
			}
			x++;
		}
	}
}

/*Draws the wand to the down center of the window.*/

void	wand(t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;

	x = 0;
	while (x < TEX_WIDTH * 2)
	{
		y = 0;
		while (y < TEX_HEIGHT * 2)
		{
			color = get_pixel_from_image(&mlx->texture[10], x * 0.5, y * 0.5);
			if (color != 0x000000)
				draw_pixel_to_image(mlx, mlx->wand.x + x,
					mlx->wand.y + y, color);
			y++;
		}
		x++;
	}
}

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

static int	dda_algorithm(t_data *data, t_ray *ray)
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
	if (data->map->matrix[ray->map_x][ray->map_y] == 2)
		return (1);
	return (0);
}

void	draw_object_raycasting(t_data *data, int x, t_image *texture)
{
	double		cam_position;
	t_ray		ray;
	t_object	object;
	int			y;
	int			color;
	double		step;
	double		tex_y;
	double		tex_x;

	(void)texture;
	cam_position = 2.0 * x / (double)WIDTH - 1.0;
	ray.direction.x = data->player->direction.x
		+ data->player->cam_plane.x * cam_position;
	ray.direction.y = data->player->direction.y
		+ data->player->cam_plane.y * cam_position;
	ray.map_x = data->player->position.x;
	ray.map_y = data->player->position.y;
	ray_steps(data, &ray);
	object.hit = 0;
	while (!object.hit)
		object.hit = dda_algorithm(data, &ray);
	if (object.hit == 1)
	{
		object.position.x = ray.map_x;
		object.position.y = ray.map_y;
		printf("X %f\n", object.position.x);
		printf("Y %f\n\n", object.position.y);
	}
	else
		return ;
	object.distance.x = object.position.x - data->player->position.x;
	object.distance.y = object.position.y - data->player->position.y;
	object.transform.x = (1.0 / data->player->cam_plane.x * data->player->direction.y - data->player->direction.x * data->player->cam_plane.y) * (data->player->direction.y * object.distance.x - data->player->direction.x * object.distance.y);
	object.transform.y = (1.0 / data->player->cam_plane.x * data->player->direction.y - data->player->direction.x * data->player->cam_plane.y) * (-data->player->cam_plane.y * object.distance.x + data->player->cam_plane.x * object.distance.y);
	object.height = ft_abs((int)(HEIGHT / object.transform.y));
	object.start_y = -object.height / 2 + HEIGHT / 2;
	if (object.start_y < 0)
		object.start_y = 0;
	object.end_y = object.height / 2 + HEIGHT / 2;
	if (object.end_y > HEIGHT - 1)
		object.end_y = HEIGHT - 1;
	object.start_x = -object.height / 2 + ((int)(WIDTH / 2) * (1 + object.transform.x / object.transform.y));
	if (object.start_x < 0)
		object.start_x = 0;
	object.end_x = object.height / 2 + ((int)(WIDTH / 2) * (1 + object.transform.x / object.transform.y));
	if (object.end_x > WIDTH - 1)
		object.end_x = WIDTH - 1;
	printf("START Y %d\n", object.start_y);
	printf("START X %d\n", object.start_x);
	printf("END Y %d\n", object.end_y);
	printf("END X %d\n\n", object.end_x);
	if ((ray.grid.x - ray.delta.x) > (ray.grid.y - ray.delta.y))
		ray.length = ray.grid.x - ray.delta.x;
	else
		ray.length = ray.grid.y - ray.delta.y;
	printf("LENGTH %f\n", ray.length);
	step = 1.0 * TEX_HEIGHT / object.height;
	tex_y = 0;
	tex_x = (x - object.start_x) * step;
	if (tex_x < 0 || tex_x > TEX_WIDTH)
		return ;
	y = object.start_y;
	printf("TEX X %f\n", tex_x);
	while (y < object.end_y)
	{
		//if (ray.length < data->mlx->depth[x])
		//	draw_pixel_to_image(data->mlx, x, y, 0x000000);
		color = get_pixel_from_image(&texture[8], tex_x, tex_y);
		if (ray.length < data->mlx->depth[x])
			draw_pixel_to_image(data->mlx, x, y, color);
		tex_y += step;
		y++;
	}
}

void	*objects(void *thread)
{
	t_data		*data;
	int			x;

	data = (t_data *)thread;
	x = data->start_x;
	while (x < data->end_x)
	{
		draw_object_raycasting(data, x, data->mlx->texture);
		x++;
	}
	pthread_exit(NULL);
}
