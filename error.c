/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:26:29 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/09/13 13:43:10 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Prints error message and exits properly.*/

void	error(const char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}

/*Frees the saved map string that has allocated space before an error occured 
 * and closes the opened file.*/

void	buff_error(char *saved_map, int file)
{
	int		closing;

	free(saved_map);
	closing = close(file);
	if (closing == -1)
		error("Error: Unable to close file and get map info.");
	error("Error: Couldn't get map information.");
}

/*Frees all memory allocated before an error occured.*/

void	matrix_error(char **matrix, char *saved_map, int index)
{
	while (index >= 0)
		free(matrix[index--]);
	if (matrix)
		free(matrix);
	if (saved_map)
		free(saved_map);
	error("Error: Couldn't get map information.");
}
