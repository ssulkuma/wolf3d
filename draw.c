/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:00 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/05 15:26:10 by ssulkuma         ###   ########.fr       */
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

/*Iterates through every pixel on the x-axis of the thread.*/

static void	*draw(void *data)
{
	t_data				*thread;
	int					x;

	thread = (t_data *)data;
	x = thread->start_x;
	while (x < thread->end_x)
	{
		wall_raycasting(thread, x, thread->mlx->texture);
		objects(thread, thread->mlx->texture);
		x++;
	}
	pthread_exit(NULL);
}

/*Counts the width for every thread, so that the image will be drawn in
 * parts. Creates the threads and waits for all of the tasks to be done
 * the same time, before pushing the image to the window.*/

void	create_threads(t_mlx *mlx, t_map *map, t_player *player)
{
	int			index;
	pthread_t	thread_id[THREADS];
	t_data		thread[THREADS];

	index = -1;
	while (++index < THREADS)
	{
		thread[index].start_x = WIDTH / THREADS * index;
		thread[index].end_x = WIDTH / THREADS * (index + 1);
		thread[index].mlx = mlx;
		thread[index].map = map;
		thread[index].player = player;
	}
	index = -1;
	skybox(&thread[0], mlx->texture);
	floor_raycasting(&thread[0], mlx->texture);
	while (++index < THREADS)
		pthread_create(&thread_id[index], NULL, draw, &thread[index]);
	index = -1;
	while (++index < THREADS)
		pthread_join(thread_id[index], NULL);
	mlx_put_image_to_window(mlx->connection, mlx->window,
		mlx->image->image, 0, 0);
}
