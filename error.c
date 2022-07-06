/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:26:29 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/06 13:33:48 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Prints error message and exits properly.*/

void	error(const char *str)
{
	perror(str);
	exit(1);
}

/*Frees the saved map string that has allocated space before an error occured 
 * and closes the opened file.*/

void	buff_error(char *saved_map, int file)
{
	free(saved_map);
	close(file);
	ft_putendl("error");
}

/*Frees all memory allocated before an error occured.*/

void	matrix_error(char **matrix, char *saved_map, int index)
{
	while (index > 0)
		free(matrix[index--]);
	if (matrix)
		free(matrix);
	if (saved_map)
		free(saved_map);
	error("error");
}
