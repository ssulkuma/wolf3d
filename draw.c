/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:00 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/21 10:23:52 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Function to color a pixel in an image.*/

void	draw_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = mlx->image->address + (y * mlx->image->line_len + \
			x * (mlx->image->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

int	get_pixel_from_image(t_image *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->address + (y * texture->line_len + \
		x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

static void	get_textures(t_image *texture)
{
	int		x;
	int		y;

	x = TEX_WIDTH;
	y = TEX_HEIGHT;
	texture[0].image = mlx_xpm_file_to_image(&texture[0], TEX_0, &x, &y);
	texture[1].image = mlx_xpm_file_to_image(&texture[1], TEX_1, &x, &y);
	texture[2].image = mlx_xpm_file_to_image(&texture[2], TEX_2, &x, &y);
	texture[3].image = mlx_xpm_file_to_image(&texture[3], TEX_3, &x, &y);
	texture[0].address = mlx_get_data_addr(texture[0].image,
		&texture[0].bits_per_pixel, &texture[0].line_len, &texture[0].endian);
	texture[1].address = mlx_get_data_addr(texture[1].image,
		&texture[1].bits_per_pixel, &texture[1].line_len, &texture[1].endian);
	texture[2].address = mlx_get_data_addr(texture[2].image,
		&texture[2].bits_per_pixel, &texture[2].line_len, &texture[2].endian);
	texture[3].address = mlx_get_data_addr(texture[3].image,
		&texture[3].bits_per_pixel, &texture[3].line_len, &texture[3].endian);
	//mlx_put_image_to_window(mlx->connection, mlx->window, texture[0].image, 0, 0);
	//mlx_put_image_to_window(mlx->connection, mlx->window, texture[1].image, 70, 0);
	//mlx_put_image_to_window(mlx->connection, mlx->window, texture[2].image, 140, 0);
	//mlx_put_image_to_window(mlx->connection, mlx->window, texture[3].image, 210, 0);
}

/*Iterates through every pixel on the thread.*/

static void	*draw(void *data)
{
	t_image		texture[MAX_TEXTURES];
	t_data		*thread;
	int			x;
	int			y;

	thread = (t_data *)data;
	get_textures(texture);
	x = thread->start_x;
	while (x < thread->end_x)
	{
		y = 0;
		raycasting(thread, x, texture);
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
	mlx_put_image_to_window(mlx->connection, mlx->window, mlx->image->image, 0, 0);
}
