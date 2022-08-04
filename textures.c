/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:53:13 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/04 14:46:09 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	wall_and_floor_textures(t_image *texture)
{
	int		x;
	int		y;

	x = TEX_WIDTH;
	y = TEX_HEIGHT;
	texture[0].image = mlx_xpm_file_to_image(&texture[0], TEX_0, &x, &y);
	texture[0].address = mlx_get_data_addr(texture[0].image,
			&texture[0].bits_per_pixel, &texture[0].len, &texture[0].endian);
	texture[1].image = mlx_xpm_file_to_image(&texture[1], TEX_1, &x, &y);
	texture[1].address = mlx_get_data_addr(texture[1].image,
			&texture[1].bits_per_pixel, &texture[1].len, &texture[1].endian);
	texture[2].image = mlx_xpm_file_to_image(&texture[2], TEX_2, &x, &y);
	texture[2].address = mlx_get_data_addr(texture[2].image,
			&texture[2].bits_per_pixel, &texture[2].len, &texture[2].endian);
	texture[3].image = mlx_xpm_file_to_image(&texture[3], TEX_3, &x, &y);
	exture[3].address = mlx_get_data_addr(texture[3].image,
			&texture[3].bits_per_pixel, &texture[3].len, &texture[3].endian);
	texture[4].image = mlx_xpm_file_to_image(&texture[4], TEX_4, &x, &y);
	texture[4].address = mlx_get_data_addr(texture[4].image,
			&texture[4].bits_per_pixel, &texture[4].len, &texture[4].endian);
}

static void	skybox_textures(t_image *texture)
{
	int		x;
	int		y;

	x = SKYBOX_TEX_WIDTH;
	y = SKYBOX_TEX_HEIGHT;
	texture[5].image = mlx_xpm_file_to_image(&texture[5], TEX_5, &x, &y);
	texture[5].address = mlx_get_data_addr(texture[5].image,
			&texture[5].bits_per_pixel, &texture[5].len, &texture[5].endian);
	texture[6].image = mlx_xpm_file_to_image(&texture[5], TEX_6, &x, &y);
	texture[6].address = mlx_get_data_addr(texture[6].image,
			&texture[6].bits_per_pixel, &texture[6].len, &texture[6].endian);
}

static void	object_textures(t_image *texture)
{
	int		x;
	int		y;

	x = TEX_WIDTH;
	y = TEX_HEIGHT;
	texture[7].image = mlx_xpm_file_to_image(&texture[7], TEX_7, &x, &y);
	texture[7].address = mlx_get_data_addr(texture[7].image,
			&texture[7].bits_per_pixel, &texture[7].len, &texture[7].endian);
	texture[8].image = mlx_xpm_file_to_image(&texture[8], TEX_8, &x, &y);
	texture[8].address = mlx_get_data_addr(texture[8].image,
			&texture[8].bits_per_pixel, &texture[8].len, &texture[8].endian);
	texture[9].image = mlx_xpm_file_to_image(&texture[9], TEX_9, &x, &y);
	texture[9].address = mlx_get_data_addr(texture[9].image,
			&texture[9].bits_per_pixel, &texture[9].len, &texture[9].endian);
	texture[10].image = mlx_xpm_file_to_image(&texture[10], TEX_10, &x, &y);
	texture[10].address = mlx_get_data_addr(texture[10].image,
			&texture[10].bits_per_pixel, &texture[10].len, &texture[10].endian);
	texture[11].image = mlx_xpm_file_to_image(&texture[11], TEX_11, &x, &y);
	texture[11].address = mlx_get_data_addr(texture[11].image,
			&texture[11].bits_per_pixel, &texture[11].len, &texture[11].endian);
}

/*Saves the texture information to an image from a .xpm file.*/

void	get_textures(t_image *texture)
{
	wall_and_floor_textures(texture);
	skybox_textures(texture);
	object_textures(texture);
}
