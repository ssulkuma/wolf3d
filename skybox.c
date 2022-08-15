/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:32:19 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/15 12:32:11 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Calculates the scale needed for the skybox texture, then gets color and
 * draws the pixel for every screen coordinate.*/

static void	draw_skybox(t_data *data, t_image *texture, t_skybox *skybox)
{
	int			x;
	int			y;

	skybox->step.x = (double)SKYBOX_TEX_WIDTH  / 2.0 / (double)WIDTH;
	skybox->step.y = (double)SKYBOX_TEX_HEIGHT / ((double)HEIGHT / 2);
	skybox->tex.y = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		skybox->tex.x = SKYBOX_TEX_WIDTH - (skybox->result / 360)
			* SKYBOX_TEX_WIDTH;
		while (x < WIDTH)
		{
			skybox->color = get_pixel_from_image(&texture[6], skybox->tex.x,
					skybox->tex.y);
			draw_pixel_to_image(data->mlx, x, y, skybox->color);
			skybox->tex.x += skybox->step.x;
			if (skybox->tex.x > SKYBOX_TEX_WIDTH)
				skybox->tex.x -= SKYBOX_TEX_WIDTH;
			x++;
		}
		skybox->tex.y += skybox->step.y;
		y++;
	}
}

/*Calculates the range from the player direction.*/

void	skybox(t_data *data, t_image *texture)
{
	t_skybox	skybox;

	skybox.result = atan2(data->player->direction.y, data->player->direction.x);
	if (skybox.result < 0)
		skybox.result = skybox.result + 2.0 * PI;
	skybox.result = skybox.result * 180.0 / PI;
	draw_skybox(data, texture, &skybox);
}
