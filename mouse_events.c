/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:03:59 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/23 13:49:14 by ssulkuma         ###   ########.fr       */
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

int	wand_animation(t_mlx *mlx)
{
	printf("2\n");
	while (mlx->wand.x <= 500)
	{
		render(mlx);
		mlx->wand.x += ANIMATION_DURATION;
		mlx->wand.y -= ANIMATION_DURATION;
	}
	while (mlx->wand.x >= 340)
	{
		render(mlx);
		mlx->wand.x -= ANIMATION_DURATION;
		mlx->wand.y += ANIMATION_DURATION;
	}
	mlx->click = 0;
	return (0);
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
