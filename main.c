/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:53:53 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/20 13:12:29 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*
static void	get_textures(t_mlx *mlx, t_image *texture)
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
	mlx_put_image_to_window(mlx->connection, mlx->window, texture[0].image, 0, 0);
	mlx_put_image_to_window(mlx->connection, mlx->window, texture[1].image, 70, 0);
	mlx_put_image_to_window(mlx->connection, mlx->window, texture[2].image, 140, 0);
	mlx_put_image_to_window(mlx->connection, mlx->window, texture[3].image, 210, 0);
}
*/
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
	struct_intel(&mlx, &player, &image);
	mlx.image = &image;
	//get_textures(&mlx, texture);
	create_threads(&mlx, &map, &player);
	mlx.map = &map;
	mlx.player = &player;
	mlx_hook(mlx.window, 2, 0, key_events, &mlx);
	mlx_hook(mlx.window, 4, 0, mouse_events, &mlx);
	mlx_hook(mlx.window, 17, 0, close_window_event, &mlx);
	mlx_loop(mlx.connection);
	return (0);
}
