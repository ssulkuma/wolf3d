/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:37:20 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/07/01 16:36:15 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	create_matrix(char *saved_map, t_map *map)
{
	char	**matrix;
	char	**numbers;
	int		height;
	int		width;

	matrix = ft_strsplit(saved_map, '\n');
	map->width = 0;
	map->height = 0;
	while (matrix[map->width][map->height] != '\0')
		map->height++;
	while (matrix[map->width])
		map->width++;
	height = 0;
	width = 0;
	while (height < map->height)
	{
		numbers = ft_strsplit(matrix[height], ',');
		while (width < map->width)
		{
			map->matrix[height][width] = ft_atoi(numbers[width]);
			free(numbers[width]);
			width++;
		}
		free(matrix[height]);
		height++;
	}
	free(matrix);
	free(numbers);
}

static void	buff_error(char *saved_map, int file)
{
	free(saved_map);
	close(file);
	error("error");
}

static void	read_file(int file, t_map *map)
{
	char	*buff;
	char	*temp;
	char	*saved_map;
	int		read_value;

	saved_map = ft_strnew(1);
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
		saved_map = ft_strdup(temp);
		free(temp);
	}
	free(buff);
	create_matrix(saved_map, map);
	free(saved_map);
}

void	read_map(char *map_file, t_map *map)
{
	int	file;

	file = open(map_file, O_RDONLY);
	if (file == -1)
		error("error");
	read_file(file, map);
	close(file);
}
