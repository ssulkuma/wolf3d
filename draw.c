/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:55:00 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/08 17:50:21 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

static void	algorithm()
{
}

static void	raycasting()
{
	t_vector	ray;
	t_vector	ray_position;
	double		cam_position;
	int			x;
	t_vector	player;
	t_vector	direction;
	t_vector	cam_plane;

	player.x = 12;
	player.y = 12;
	direction.x = -1;
	direction.y = 0;
	cam_plane.x = 0;
	cam_plane.y = 0.66;
	x = 0;
	while (x < WIDTH)
	{
		cam_position = 2 * x / WIDTH - 1;
		ray.x = direction.x + cam_plane.x * cam_position;
		ray.y = direction.y + cam_plane.y * cam_position;
		x++;
	}
}

static void	*draw(void *data)
{
	t_thread	*thread;
	int			x;
	int			y;

	thread = (t_thread *)data;
	x = thread->start_x;
	while (x < thread->end_x)
	{
		y = 0;
		while (y < HEIGHT)
		{
			draw_pixel_to_image(thread->mlx, x, y, 0x3A243B);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}

void	create_threads(t_mlx *mlx)
{
	int			index;
	pthread_t	thread_id[THREADS];
	t_thread	thread[THREADS];

	index = -1;
	while (++index < THREADS)
	{
		thread[index].start_x = WIDTH / THREADS * index;
		thread[index].end_x = WIDTH / THREADS * (index + 1);
		thread[index].mlx = mlx;
	}
	index = -1;
	while (++index < THREADS)
		pthread_create(&thread_id[index], NULL, draw, &thread[index]);
	index = -1;
	while (++index < THREADS)
		pthread_join(thread_id[index], NULL);
	mlx_put_image_to_window(mlx->connection, mlx->window, mlx->image, 0, 0);
}
