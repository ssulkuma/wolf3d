/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:39:58 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/24 13:33:26 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*A continues mlx loop that renders the image with every frame. Upon a mouse
 * click, moves wand texture and increases scale value of fire texture to create
 * an animation.*/

int	spell_cast_animation(t_mlx *mlx)
{
	static int	duration;

	if (duration < ANIMATION_DURATION && mlx->click == 1)
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
		duration++;
	}
	else
	{
		mlx->fire_scale = 0;
		mlx->click = 0;
		mlx->wand_done = 0;
		duration = 0;
		render(mlx);
	}
	return (0);
}
