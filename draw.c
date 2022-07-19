/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:00 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/19 15:54:11 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Function to color a pixel in an image.*/

void	draw_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = mlx->address + (y * mlx->line_len + \
			x * (mlx->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

int	get_pixel_from_image(t_mlx *mlx, int x, int y)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = mlx->address + (y * mlx->line_len + \
			x * (mlx->bits_per_pixel / 8));
		return (*(unsigned int *)pixel);
	}
	return (0);
}

/**/

void	get_textures(t_mlx *mlx)
{
	t_texture	texture[MAX_TEXTURES];
	int			index;
	int			x;
	int			y;

	index = 0;
	x = 512;
	y = 64;
	while (index < MAX_TEXTURES)
	{
		texture[index].image = mlx_xpm_file_to_image(&texture[index], "./textures/wolftextures.xpm", &x, &y);
		texture[index].address = mlx_get_data_addr(texture[index].image, 
				&texture[index].bits_per_pixel, &texture[index].line_len, &texture[index].endian);
		index++;
	}
	mlx_put_image_to_window(mlx->connection, mlx->window, texture[0].image, 0, 0);
}

/*Iterates through every pixel on the thread.*/

static void	*draw(void *data)
{
	t_data		*thread;
	int			x;
	int			y;

	thread = (t_data *)data;
	x = thread->start_x;
	while (x < thread->end_x)
	{
		y = 0;
		raycasting(thread, x);
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
	while (++index < THREADS)
		pthread_create(&thread_id[index], NULL, draw, &thread[index]);
	index = -1;
	while (++index < THREADS)
		pthread_join(thread_id[index], NULL);
	mlx_put_image_to_window(mlx->connection, mlx->window, mlx->image, 0, 0);
}
