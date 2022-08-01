/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:32:19 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/01 13:52:21 by ssulkuma         ###   ########.fr       */
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
	double	result;

	result = atan2(data->player->direction.y, data->player->direction.x);
	if (result < 0)
		result = result + 2.0 * PI;
	result = result * 180.0 / PI;
	printf("RESULT %f\n", result);
	step_x = (double)SKYBOX_TEX_WIDTH / 4.0 / (double)WIDTH;
	step_y = (double)SKYBOX_TEX_HEIGHT / (double)HEIGHT;
	printf("STEP X %f\n", step_x);
	printf("STEP Y %f\n", step_y);
	tex_y = 0;
	tex_x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		tex_x = 360 - result;
		while (x < WIDTH)
		{
			//printf("TEX X %f\n", tex_x);
			//printf("X %d\n", x);
			//printf("Y %d\n\n", y);
			color = get_pixel_from_image(&texture[5], tex_x, tex_y);
			draw_pixel_to_image(data->mlx, x, y, color);
			tex_x += step_x;
			x++;
		}
		tex_y += step_y;
		y++;
	}
}
