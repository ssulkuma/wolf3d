/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:33:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/05 15:26:07 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	objects(t_data *data, t_image *texture)
{
	t_object	object;
	int			index;

	index = 0;
	while (index < data->mlx->map->object_count)
	{
		//printf("DEPTH %f\n", data->depth[index]);
		(void)object;
		(void)texture;
		index++;
	}
}
