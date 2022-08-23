/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:03:59 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/23 16:34:46 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Function to be called when closing the window from 'X'. Destroys the created
 * image and window, before exiting properly.*/

int	close_window_event(t_mlx *mlx)
{
	mlx_destroy_image(mlx->connection, mlx->image->image);
	mlx_destroy_window(mlx->connection, mlx->window);
	exit(0);
}

/*Function to be called when any mouse down related events are triggered.*/

int	mouse_events(int button, int x, int y, t_mlx *mlx)
{
	if (button == MOUSE_LEFT)
	{
		mlx->click += 1;
		mlx->fire.x = x;
		mlx->fire.y = y;
	}
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}
