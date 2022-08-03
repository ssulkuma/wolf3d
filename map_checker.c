/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:22:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/08/03 16:04:31 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Counts how many objects are within the map. Objects are represented as 6, 7
 * and 8 in the map.*/

void	count_objects_in_map(char *saved_map, t_map *map)
{
	int		index;

	map->object_count = 0;
	index = 0;
	while (saved_map[index] != '\0')
	{
		if ((saved_map[index] >= '6' && saved_map[index] <= '8')
			&& (saved_map[index + 1] == ',' || saved_map[index + 1] == '\n'
			|| saved_map[index + 1] == '\0') && (saved_map[index - 1] == ','
			|| saved_map[index - 1] == '\n' || index == 0))
			map->object_count++;
		index++;
	}
	printf("OBJ COUNT %d\n", map->object_count);
}

/*Checks that the map file only consists of digits, newlines and single commas
 * between the digits.*/

void	check_map_characters(char *saved_map)
{
	int		index;

	index = 0;
	if (saved_map[index] == '\0')
		error("Error: Invalid map.");
	if (saved_map[index] < '0' || saved_map[index] > '9')
		error("Error: Invalid map.");
	while (saved_map[index] != '\0')
	{
		if ((saved_map[index] >= '0' && saved_map[index] <= '9')
			|| saved_map[index] == ',' || saved_map[index] == '\n')
		{
			if (saved_map[index] == ',')
			{
				if (saved_map[index + 1] < '0' || saved_map[index + 1] > '9')
					error("Error: Invalid map.");
			}
		}
		else
			error("Error: Invalid map.");
		index++;
	}
}

/*Checks that map width is equal in every row.*/

void	check_map_size(char **matrix, t_map *map)
{
	int		height;
	int		width;
	int		width_check;

	height = 0;
	while (height < map->height)
	{
		width = 0;
		width_check = 0;
		while (matrix[height][width] != '\0')
		{
			if (matrix[height][width] == ',')
				width_check++;
			width++;
		}
		width_check += 1;
		if (width_check != map->width)
			error("Error: Invalid map.");
		height++;
	}
}
