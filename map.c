/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:37:20 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/06 13:12:28 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Function to get map width and height.*/

static void	get_map_size(char **matrix, t_map *map)
{
	int		height;
	int		width;

	map->width = 1;
	map->height = 0;
	width = 0;
	height = 0;
	while (matrix[height][width] != '\0')
	{
		if (matrix[height][width] == ',')
			map->width++;
		width++;
	}
	while (matrix[map->height])
		map->height++;
}

/*Helper function for create_matrix. Converts the char numbers to ints.*/

static void	matrix_help(int height, t_map *map, char *saved_map, char **matrix)
{
	char	**numbers;
	int		width;

	map->matrix[height] = (int *)malloc(sizeof(int) * (map->width + 1));
	if (!map->matrix[height])
		matrix_error(matrix, saved_map, height);
	numbers = ft_strsplit(matrix[height], ',');
	if (!numbers)
		matrix_error(matrix, saved_map, height);
	width = 0;
	while (width < map->width)
	{
		map->matrix[height][width] = ft_atoi(numbers[width]);
		free(numbers[width]);
		width++;
	}
	free(numbers);
}

/*Transforms the saved map string first to a 2D char array to get final
 * matrix size, before allocating enough memory for the 2D int array,
 * where the map information is stored to be used later on when drawing.*/

static void	create_matrix(char *saved_map, t_map *map)
{
	char	**matrix;
	int		height;

	matrix = ft_strsplit(saved_map, '\n');
	if (!matrix)
		matrix_error(matrix, saved_map, 0);
	get_map_size(matrix, map);
	map->matrix = (int **)malloc(sizeof(int *) * (map->height + 1));
	if (!map->matrix)
		matrix_error(matrix, saved_map, 0);
	height = 0;
	while (height < map->height)
	{
		matrix_help(height, map, saved_map, matrix);
		free(matrix[height]);
		height++;
	}
	free(matrix);
}

/*Reads from file into the buffer and saves the information to a string.*/

static void	read_file(int file, t_map *map, char *saved_map)
{
	char	*buff;
	char	*temp;
	int		read_value;

	while (1)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			buff_error(saved_map, file);
		read_value = read(file, buff, BUFFER_SIZE);
		if (read_value < 1)
			break ;
		buff[read_value] = '\0';
		temp = ft_strjoin(saved_map, buff);
		free(buff);
		free(saved_map);
		if (!temp)
			return ;
		saved_map = ft_strdup(temp);
		free(temp);
	}
	free(buff);
	saved_map = NULL;
	create_matrix(saved_map, map);
	free(saved_map);
}

/*Opens the map file for reading and creates the string the map will
 * be saved to.*/

void	read_map(char *map_file, t_map *map)
{
	int		file;
	char	*saved_map;

	file = open(map_file, O_RDONLY);
	if (file == -1)
		error("error");
	saved_map = ft_strnew(1);
	if (!saved_map)
	{
		close(file);
		error("error");
	}
	read_file(file, map, saved_map);
	close(file);
}
