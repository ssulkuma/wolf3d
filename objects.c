/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:33:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/23 16:22:51 by ssulkuma         ###   ########.fr       */
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

	if (mlx->click)
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
/*
void	*objects(void *thread)
{
	t_data		*data;
	t_object	object;
	int			index;

	data = (t_data *)data;
	index = 0;
	while (index < data->mlx->map->object_count)
	{
		//printf("DEPTH %f\n", data->depth[index]);
		index++;
	}
}*/
