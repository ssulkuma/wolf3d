/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:00 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/23 16:33:14 by ssulkuma         ###   ########.fr       */
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

static void	*wall_raycasting(void *thread)
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

/*Counts the width or height for every thread, so that the image will be
 * drawn in parts. Creates the threads and waits for all of the tasks to be
 * done the same time.*/

void	create_threads(t_mlx *mlx, void *(*function)(void *))
{
	int			index;
	pthread_t	thread_id[THREADS];
	t_data		thread[THREADS];

	index = -1;
	while (++index < THREADS)
	{
		thread[index].start_x = WIDTH / THREADS * index;
		thread[index].end_x = WIDTH / THREADS * (index + 1);
		thread[index].start_y = (HEIGHT / 2) / THREADS * index;
		thread[index].end_y = (HEIGHT / 2) / THREADS * (index + 1);
		thread[index].mlx = mlx;
		thread[index].map = mlx->map;
		thread[index].player = mlx->player;
	}
	index = -1;
	while (++index < THREADS)
		pthread_create(&thread_id[index], NULL, function, &thread[index]);
	index = -1;
	while (++index < THREADS)
		pthread_join(thread_id[index], NULL);
}

/*This is where the image rendering happens. Sends the correct function pointers
 * to the multithreading function in the right order and after each part is
 * done, puts the image to the window.*/

void	render(t_mlx *mlx)
{
	create_threads(mlx, &skybox);
	create_threads(mlx, &floor_raycasting);
	create_threads(mlx, &wall_raycasting);
	//create_threads(mlx, &objects);
	fire(mlx);
	wand(mlx);
	mlx_put_image_to_window(mlx->connection, mlx->window,
		mlx->image->image, 0, 0);
}
