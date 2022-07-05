/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:26:29 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/05 14:32:12 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error(const char *str)
{
	perror(str);
	exit(1);
}

void	buff_error(char *saved_map, int file)
{
	free(saved_map);
	close(file);
	error("error");
}

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
