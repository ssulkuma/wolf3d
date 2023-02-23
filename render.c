/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:52:24 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/23 10:47:13 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
 * done, puts the image to the window. Holds menu information and puts it to
 * the image.*/

void	render(t_mlx *mlx)
{
	char	*menu[4];
	int		index;

	menu[0] = "C O N T R O L S";
	menu[1] = "[arrows / WASD] move";
	menu[2] = "[mouse] cast a spell";
	menu[3] = "[M] close menu";
	create_threads(mlx, &skybox);
	create_threads(mlx, &floor_raycasting);
	create_threads(mlx, &wall_raycasting);
	create_threads(mlx, &objects);
	fire(mlx);
	wand(mlx);
	mlx_put_image_to_window(mlx->connection, mlx->window,
		mlx->image->image, 0, 0);
	if (mlx->menu)
	{
		index = -1;
		while (++index < 4)
			mlx_string_put(mlx->connection, mlx->window, 100,
				200 + (index * 20), 0xFFFFFF, menu[index]);
	}
	else
		mlx_string_put(mlx->connection, mlx->window,
			700, 610, 0xFFFFFF, "[M] MENU");
}
