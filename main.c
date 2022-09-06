/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:53:53 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/06 10:59:27 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Initializes the struct variables for starting position of player, wand
 * placement and other needed information.*/

static void	init_helper(t_mlx *mlx, t_player *player)
{
	player->direction.x = -1;
	player->direction.y = 0;
	player->cam_plane.x = 0;
	player->cam_plane.y = 0.66;
	player->move_speed = 0.3;
	player->turn_speed = 0.075;
	mlx->fire.x = 0;
	mlx->fire.y = 0;
	mlx->wand.x = 340;
	mlx->wand.y = 512;
	mlx->fire_scale = 0.0;
	mlx->click = 0;
	mlx->menu = 0;
}

/*Initializes the struct variables needed to open a graphic window and the
 * starting position for player.*/

static void	init(t_mlx *mlx, t_player *player, t_image *screen, t_map *map)
{
	mlx->connection = mlx_init();
	if (!mlx->connection)
		error("Error: Unable to open mlx connection.");
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "Wolf3D");
	if (!mlx->window)
		error("Error: Unable create a new window.");
	screen->image = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	screen->address = mlx_get_data_addr(screen->image, &screen->bits_per_pixel,
			&screen->len, &screen->endian);
	player->position.x = 2;
	player->position.y = 2;
	if (player->position.x < 1 || player->position.x > map->width
		|| player->position.y < 1 || player->position.y > map->height)
		error("Error: Player starting position outside of map bounds.");
	init_helper(mlx, player);
}

/*List of mlx hooks that are triggered by certain events. Calls the function
 * for the continues loop, which renders the image each frame.*/

static void	hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 0, key_events, mlx);
	mlx_hook(mlx->window, 4, 0, mouse_events, mlx);
	mlx_hook(mlx->window, 17, 0, close_window_event, mlx);
	mlx_loop_hook(mlx->connection, spell_cast_animation, mlx);
	mlx_loop(mlx->connection);
}

/*Start of program. Displays usage message in case of misusage.*/

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_image		image;
	t_image		texture[MAX_TEXTURES];

	if (argc != 2)
	{
		ft_putendl("Usage: ./wolf3d [map]");
		return (1);
	}
	read_map(argv[1], &map);
	init(&mlx, &player, &image, &map);
	get_textures(texture);
	mlx.image = &image;
	mlx.texture = texture;
	mlx.map = &map;
	mlx.player = &player;
	render(&mlx);
	hooks(&mlx);
	return (0);
}
