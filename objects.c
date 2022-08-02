/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:33:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/02 15:35:43 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	objects(t_data *data, t_image *texture)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			color = get_pixel_from_image(&texture[6], x, y);
			if (color != 0x000000)
				draw_pixel_to_image(data->mlx, x, y, color);
			x++;
		}
		y++;
	}
}
