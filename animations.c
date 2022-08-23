/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:39:58 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/23 15:18:36 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	fire_animation(t_mlx *mlx)
{
	static int	duration;

	if (duration < ANIMATION_DURATION && mlx->click == 1)
	{
		if (duration < ANIMATION_DURATION / 2)
			mlx->fire_scale += 1;
		else
			mlx->fire_scale -= 1;
		render(mlx);
		duration++;
	}
	else
	{
		mlx->fire_scale = 0;
		mlx->click = 0;
		duration = 0;
		render(mlx);
	}
	return (0);
}
