/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:33:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/22 16:33:35 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_fire(t_mlx *mlx, int x, int y, int scale)
{
	int		color;

	if (scale == 1)
	{
		color = get_pixel_from_image(&mlx->texture[11], x, y);
		if (color != 0x000000)
			draw_pixel_to_image(mlx, mlx->fire.x - 33 + x,
					mlx->fire.y - 45 + y, color);
	}
	else if (scale == 2)
	{
		color = get_pixel_from_image(&mlx->texture[11], x * 0.5, y * 0.5);
		if (color != 0x000000)
			draw_pixel_to_image(mlx, mlx->fire.x - 66 + x,
					mlx->fire.y - 90 + y, color);
	}
	else if (scale == 3)
	{
		color = get_pixel_from_image(&mlx->texture[11], x * 0.333, y * 0.333);
		if (color != 0x000000)
			draw_pixel_to_image(mlx, mlx->fire.x - 105 + x,
					mlx->fire.y - 135 + y, color);
	}
	else
	{
		color = get_pixel_from_image(&mlx->texture[11], x * 0.25, y * 0.25);
		if (color != 0x000000)
			draw_pixel_to_image(mlx, mlx->fire.x - 140 + x,
					mlx->fire.y - 180 + y, color);
	}
}

void	fire(t_mlx *mlx)
{
	int		x;
	int		y;
	int		scale;

	if (mlx->click)
	{
		if (mlx->fire.y <= 160)
			scale = 1;
		else if (mlx->fire.y > 160 && mlx->fire.y <= 320)
			scale = 2;
		else if (mlx->fire.y > 320 && mlx->fire.y <= 480)
			scale = 3;
		else
			scale = 4;
		x = 0;
		while (x < TEX_WIDTH * scale)
		{
			y = 0;
			while (y < TEX_HEIGHT * scale)
			{
				draw_fire(mlx, x, y, scale);
				y++;
			}
			x++;
		}
		mlx->click = 0;
	}
}

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
				draw_pixel_to_image(mlx, mlx->wand.x + x, mlx->wand.y + y, color);
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
