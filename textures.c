/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:53:13 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/19 16:28:38 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	wall_and_floor_textures(t_image *texture, int x, int y)
{
	texture[0].image = mlx_xpm_file_to_image(&texture[0], TEX_0, &x, &y);
	texture[0].address = mlx_get_data_addr(texture[0].image,
			&texture[0].bits_per_pixel, &texture[0].len, &texture[0].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[1].image = mlx_xpm_file_to_image(&texture[1], TEX_1, &x, &y);
	texture[1].address = mlx_get_data_addr(texture[1].image,
			&texture[1].bits_per_pixel, &texture[1].len, &texture[1].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[2].image = mlx_xpm_file_to_image(&texture[2], TEX_2, &x, &y);
	texture[2].address = mlx_get_data_addr(texture[2].image,
			&texture[2].bits_per_pixel, &texture[2].len, &texture[2].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[3].image = mlx_xpm_file_to_image(&texture[3], TEX_3, &x, &y);
	texture[3].address = mlx_get_data_addr(texture[3].image,
			&texture[3].bits_per_pixel, &texture[3].len, &texture[3].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[4].image = mlx_xpm_file_to_image(&texture[4], TEX_4, &x, &y);
	texture[4].address = mlx_get_data_addr(texture[4].image,
			&texture[4].bits_per_pixel, &texture[4].len, &texture[4].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
}

static void	skybox_textures(t_image *texture, int x, int y)
{
	texture[5].image = mlx_xpm_file_to_image(&texture[5], TEX_5, &x, &y);
	texture[5].address = mlx_get_data_addr(texture[5].image,
			&texture[5].bits_per_pixel, &texture[5].len, &texture[5].endian);
	if (x != SKYBOX_TEX_WIDTH || y != SKYBOX_TEX_HEIGHT)
		error("Error: Incorrect texture size.");
}

static void	object_textures(t_image *texture, int x, int y)
{
	texture[6].image = mlx_xpm_file_to_image(&texture[6], TEX_6, &x, &y);
	texture[6].address = mlx_get_data_addr(texture[6].image,
			&texture[6].bits_per_pixel, &texture[6].len, &texture[6].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[7].image = mlx_xpm_file_to_image(&texture[7], TEX_7, &x, &y);
	texture[7].address = mlx_get_data_addr(texture[7].image,
			&texture[7].bits_per_pixel, &texture[7].len, &texture[7].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[8].image = mlx_xpm_file_to_image(&texture[8], TEX_8, &x, &y);
	texture[8].address = mlx_get_data_addr(texture[8].image,
			&texture[8].bits_per_pixel, &texture[8].len, &texture[8].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[9].image = mlx_xpm_file_to_image(&texture[9], TEX_9, &x, &y);
	texture[9].address = mlx_get_data_addr(texture[9].image,
			&texture[9].bits_per_pixel, &texture[9].len, &texture[9].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
	texture[10].image = mlx_xpm_file_to_image(&texture[10], TEX_10, &x, &y);
	texture[10].address = mlx_get_data_addr(texture[10].image,
			&texture[10].bits_per_pixel, &texture[10].len, &texture[10].endian);
	if (x != TEX_WIDTH || y != TEX_HEIGHT)
		error("Error: Incorrect texture size.");
}

/*Checks that textures are the correct size.*/

static void	check_textures(t_image *texture)
{
	int		index;

	index = 0;
	while (index < MAX_TEXTURES)
	{
		if (!texture[index].image || !texture[index].address)
			error("Error: Unable to get correct texture information.");
		index++;
	}
}

/*Saves the texture information to an image from a .xpm file.*/

void	get_textures(t_image *texture)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	wall_and_floor_textures(texture, x, y);
	skybox_textures(texture, x, y);
	object_textures(texture, x, y);
	check_textures(texture);
}
