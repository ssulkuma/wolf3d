/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:53:53 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/06/30 11:32:09 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	struct_intel(t_mlx *mlx)
{
	mlx->connection = mlx_init();
	if (!mlx->connection)
		error("error");
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "Wolf3D");
	if (!mlx->window)
		error("error");
	mlx->image = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	mlx->address = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel,
			&mlx->line_len, &mlx->endian);
}

void	error(const char *str)
{
	perror(str);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 1 && argv)
	{
		ft_putendl("Usage: ./wolf3d");
		return (1);
	}
	struct_intel(&mlx);
	mlx_hook(mlx.window, 2, 0, key_events, &mlx);
	mlx_hook(mlx.window, 17, 0, close_window_event, &mlx);
	mlx_loop(mlx.connection);
	return (0);
}
