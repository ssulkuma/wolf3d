/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:53:53 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/20 11:12:33 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Initializes the struct variables needed to open a graphic window and the
 * starting position for player.*/

static void	struct_intel(t_mlx *mlx, t_player *player, t_image *screen)
{
	mlx->connection = mlx_init();
	if (!mlx->connection)
		error("Error: Unable to open mlx connection.");
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "Wolf3D");
	if (!mlx->window)
		error("Error: Unable create a new window.");
	screen->image = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	screen->address = mlx_get_data_addr(screen->image, &screen->bits_per_pixel,
			&screen->line_len, &screen->endian);
	player->position.x = 12;
	player->position.y = 12;
	player->direction.x = -1;
	player->direction.y = 0;
	player->cam_plane.x = 0;
	player->cam_plane.y = 0.66;
	player->move_speed = 0.3;
	player->turn_speed = 0.1;
}

/*Displays usage message in case of misusage. List of event hooks.*/

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_image		image;
	//t_image		texture[MAX_TEXTURES];

	if (argc != 2)
	{
		ft_putendl("Usage: ./wolf3d [map]");
		return (1);
	}
	read_map(argv[1], &map);
	printf("OK 1\n");
	struct_intel(&mlx, &player, &image);
	printf("OK 2\n");
	mlx.image = &image;
	create_threads(&mlx, &map, &player);
	printf("OK 3\n");
	get_textures(&mlx);
	printf("OK 4\n");
	mlx.map = &map;
	mlx.player = &player;
	mlx_hook(mlx.window, 2, 0, key_events, &mlx);
	mlx_hook(mlx.window, 4, 0, mouse_events, &mlx);
	mlx_hook(mlx.window, 17, 0, close_window_event, &mlx);
	mlx_loop(mlx.connection);
	return (0);
}
