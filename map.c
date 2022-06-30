/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:37:20 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/06/30 15:20:47 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	read_map(char *map, t_mlx *mlx)
{
	int	file;

	file = open(map, O_RDONLY);
	if (file == -1)
		error("error");
	mlx->window = mlx->window;
}
