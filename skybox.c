/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:32:19 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/29 15:37:44 by ssulkuma         ###   ########.fr       */
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
	result = result * 180.0 / PI;
	printf("RESULT %f\n", result);
	step_x = (double)SKYBOX_TEX_WIDTH / 4.0 / (double)WIDTH;
	step_y = (double)SKYBOX_TEX_HEIGHT / (double)HEIGHT;
	printf("STEP X %f\n", step_x);
	printf("STEP Y %f\n", step_y);
	tex_y = 0;
	tex_x = ft_fabs(result);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			//printf("TEX X %f\n", tex_x);
			//printf("TEX Y %f\n\n", tex_y);
			color = get_pixel_from_image(&texture[5], tex_x, tex_y);
			draw_pixel_to_image(data->mlx, x, y, color);
			tex_x += step_x;
			//tex_y += step_y;
			x++;
		}
		y++;
	}
}
