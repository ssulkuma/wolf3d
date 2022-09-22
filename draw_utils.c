/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:00 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/22 13:56:47 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Function to color a pixel in an image.*/

void	draw_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = mlx->image->address + (y * mlx->image->len + \
			x * (mlx->image->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

/*Function to get the color value from a specific coordinate of an image.*/

int	get_pixel_from_image(t_image *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->address + (y * texture->len + \
		x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

/*Iterates through every pixel on the x-axis of the thread in wall
 * raycasting.*/

void	*wall_raycasting(void *thread)
{
	t_data		*data;
	int			x;

	data = (t_data *)thread;
	x = data->start_x;
	while (x < data->end_x)
	{
		draw_wall_raycasting(data, x, data->mlx->texture);
		x++;
	}
	pthread_exit(NULL);
}

/*Iterates through every pixel on the x-axis of the thread in object
 * raycasting.*/

void	*objects(void *thread)
{
	t_data		*data;
	int			x;

	data = (t_data *)thread;
	x = data->start_x;
	while (x < data->end_x)
	{
		object_raycasting(data, x);
		x++;
	}
	pthread_exit(NULL);
}
