/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:03:59 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/19 19:33:50 by ssulkuma         ###   ########.fr       */
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
		create_threads(mlx, mlx->map, mlx->player);
		mlx->wand.x += ANIMATION_DURATION;
		mlx->wand.y -= ANIMATION_DURATION;
	}
	while (mlx->wand.x >= 340)
	{
		create_threads(mlx, mlx->map, mlx->player);
		mlx->wand.x -= ANIMATION_DURATION;
		mlx->wand.y += ANIMATION_DURATION;
	}
	mlx->click = 0;
	return (0);
}

int	fire_animation(t_mlx *mlx)
{
	double	duration;

	duration = 0;
	while (duration < 5)
	{
		create_threads(mlx, mlx->map, mlx->player);
		duration += ANIMATION_DURATION;
	}
	mlx->fire.x = 0;
	mlx->fire.y = 0;
	create_threads(mlx, mlx->map, mlx->player);
	return (0);
}

/*Function to be called when any mouse down related events are triggered.*/

int	mouse_events(int button, int x, int y, t_mlx *mlx)
{
	if (button == MOUSE_RIGHT)
	{
		printf("1\n");
		mlx->click = 1;
		mlx->fire.x = x;
		mlx->fire.y = y;
		//wand_animation(mlx);
		/*if (y <= 205)
		{
			mlx->fire.x = x - 33;
			mlx->fire.y = y - 45;
		}
		else if(y > 205 && y <= 410)
		{
			mlx->fire.x = x - 66;
			mlx->fire.y = y - 90;
		}
		else if (y > 410 && y <= 480)
		{
			mlx->fire.x = x - 105;
			mlx->fire.y = y - 135;
		}
		else
		{
			mlx->fire.x = x - 140;
			mlx->fire.y = y - 180;
		}*/
		create_threads(mlx, mlx->map, mlx->player);
		//mlx_loop_hook(mlx->connection, fire_animation, mlx);
	}
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}
