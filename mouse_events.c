/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:03:59 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/06/30 11:31:10 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	close_window_event(t_mlx *mlx)
{
	mlx_destroy_image(mlx->connection, mlx->image);
	mlx_destroy_window(mlx->connection, mlx->window);
	exit(0);
}
