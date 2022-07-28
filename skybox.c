/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:32:19 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/28 15:40:32 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	skybox(t_data *data, t_image *texture)
{
	int		color;
	int 	x;
	int		y;
	double	tex_x;
	double	tex_y;
	double	step_x;
	double	step_y;

	step_x = (double)(SKYBOX_TEX_WIDTH / WIDTH);
	step_y = (double)(SKYBOX_TEX_HEIGHT / (HEIGHT / 2));
	printf("STEP X %f\n", step_x);
	printf("STEP Y %f\n", step_y);
	tex_y = 0;
	tex_x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			printf("TEX X %f\n", tex_x);
			printf("TEX Y %f\n\n", tex_y);
			color = get_pixel_from_image(&texture[5], tex_x, tex_y);
			draw_pixel_to_image(data->mlx, x, y, color);
			tex_x += step_x;
			x++;
		}
		tex_y += step_y;
		y++;
	}
}
