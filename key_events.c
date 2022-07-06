/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:20:18 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/06 13:18:39 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Function to be called when any key down related events are triggered. ESC key
 * destroys the created image and window, before exiting properly.*/

int	key_events(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(mlx->connection, mlx->image);
		mlx_destroy_window(mlx->connection, mlx->window);
		exit(0);
	}
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT
		|| keycode == ARROW_DOWN || keycode == ARROW_UP)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}
