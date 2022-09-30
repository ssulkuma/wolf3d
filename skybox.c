/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:32:19 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/16 13:35:48 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Gets color from texture image and draws every pixel within every thread's
 * bounds.*/

static void	draw_skybox(t_data *data, t_image *texture, t_skybox *skybox)
{
	int			x;
	int			y;

	skybox->tex.y = data->start_y * skybox->step.y;
	y = data->start_y;
	while (y < data->end_y)
	{
		x = 0;
		skybox->tex.x = SKYBOX_TEX_WIDTH - (skybox->result / 360)
			* SKYBOX_TEX_WIDTH;
		while (x < WIDTH)
		{
			skybox->color = get_pixel_from_image(&texture[5], skybox->tex.x,
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

/*Calculates the range from the player direction and the scale needed for
 * the skybox texture.*/

void	*skybox(void *thread)
{
	t_data		*data;
	t_skybox	skybox;

	data = (t_data *)thread;
	skybox.result = atan2(data->player->direction.x, data->player->direction.y);
	if (skybox.result < 0)
		skybox.result = skybox.result + 2.0 * PI;
	skybox.result = skybox.result * 180.0 / PI;
	skybox.step.x = (double)SKYBOX_TEX_WIDTH / 2.0 / (double)WIDTH;
	skybox.step.y = (double)SKYBOX_TEX_HEIGHT / ((double)HEIGHT / 2);
	draw_skybox(data, data->mlx->texture, &skybox);
	pthread_exit(NULL);
}
