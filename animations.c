/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:39:58 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/16 13:20:02 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*A continues mlx loop that renders the image with every frame. Upon a mouse
 * click, moves wand texture and increases scale value of fire texture to create
 * an animation.*/

int	spell_cast_animation(t_mlx *mlx)
{
	static int	duration;

	if (duration++ < ANIMATION_DURATION && mlx->click == 1)
	{
		if (duration < ANIMATION_DURATION * 0.25)
			mlx->wand.x += 1;
		else if (duration < ANIMATION_DURATION * 0.5)
			mlx->wand.x -= 1;
		else if (duration < ANIMATION_DURATION * 0.75)
		{
			mlx->wand.x = 340;
			mlx->wand_done = 1;
			mlx->fire_scale += 1;
		}
		else
			mlx->fire_scale -= 1;
		render(mlx);
		return (0);
	}
	mlx->fire_scale = 0;
	mlx->click = 0;
	mlx->wand_done = 0;
	duration = 0;
	render(mlx);
	return (0);
}

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
				color = get_pixel_from_image(&mlx->texture[10], x / scale,
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
			color = get_pixel_from_image(&mlx->texture[9], x * 0.5, y * 0.5);
			if (color != 0x000000)
				draw_pixel_to_image(mlx, mlx->wand.x + x,
					mlx->wand.y + y, color);
			y++;
		}
		x++;
	}
}
