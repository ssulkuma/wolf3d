/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:37:20 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/05 15:27:23 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
}

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
	create_matrix(saved_map, map);
	free(saved_map);
}

void	read_map(char *map_file, t_map *map)
{
	int		file;
	char	*saved_map;

	file = open(map_file, O_RDONLY);
	if (file == -1)
		error("error");
	saved_map = ft_strnew(1);
	if (!saved_map)
		error("error");
	read_file(file, map, saved_map);
	close(file);
}
