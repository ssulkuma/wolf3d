/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saritasulkumaki <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:40:24 by saritasul         #+#    #+#             */
/*   Updated: 2022/03/14 10:56:31 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*start_of_next_line(const int fd, char *buff_rd, char **save_rd)
{
	char			*save;
	unsigned int	line_len;
	size_t			save_len;

	if (save_rd[fd])
		free(save_rd[fd]);
	if (ft_strchr(buff_rd, '\n') == NULL)
		return (NULL);
	line_len = 0;
	while (buff_rd[line_len] != '\n')
		line_len++;
	line_len = line_len + 1;
	save_len = (ft_strlen(buff_rd) - line_len);
	if (save_len == 0)
		return (NULL);
	save = ft_strsub(buff_rd, line_len, save_len);
	return (save);
}

static char	**if_newline(char *buff_rd, char **line)
{
	unsigned int	line_len;
	unsigned int	i;

	if (buff_rd[0] == '\n')
	{
		*line = ft_strnew(0);
		return (line);
	}
	if (ft_strchr(buff_rd, '\n') == NULL)
	{
		line[0] = ft_strdup(buff_rd);
		return (line);
	}
	line_len = 0;
	while (buff_rd[line_len] != '\n')
		line_len++;
	*line = ft_strnew(line_len);
	i = 0;
	while (i < line_len)
	{
		line[0][i] = buff_rd[i];
		i++;
	}
	return (line);
}

static char	*read_fd(const int fd, int *ret_value)
{
	char	*buff;
	char	*ret;
	int		rd_value;

	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
		return (NULL);
	rd_value = read(fd, buff, BUFF_SIZE);
	if (rd_value < 1)
	{
		free(buff);
		if (rd_value == -1)
			*ret_value = -1;
		return (NULL);
	}
	buff[rd_value] = '\0';
	ret = ft_strdup(buff);
	free(buff);
	return (ret);
}

static char	*no_newline(const int fd, char *buff_rd, int *ret_value)
{
	char	*next_buff_rd;
	char	*temp;

	while (ft_strchr(buff_rd, '\n') == NULL)
	{
		next_buff_rd = read_fd(fd, ret_value);
		if (!next_buff_rd)
			break ;
		temp = ft_strjoin(buff_rd, next_buff_rd);
		free(buff_rd);
		free(next_buff_rd);
		buff_rd = ft_strdup(temp);
		free(temp);
	}
	return (buff_rd);
}

int	get_next_line(const int fd, char **line)
{
	static char	*save_rd[4096];
	char		*buff_rd;
	int			ret_value;

	if (fd < 0 || fd > 4097 || BUFF_SIZE < 1 || !line)
		return (-1);
	ret_value = 0;
	if (!save_rd[fd])
		buff_rd = read_fd(fd, &ret_value);
	else
		buff_rd = ft_strdup(save_rd[fd]);
	if (!save_rd[fd] && !buff_rd)
		return (ret_value);
	buff_rd = no_newline(fd, buff_rd, &ret_value);
	line = if_newline(buff_rd, line);
	if (ft_strchr(buff_rd, '\n') == NULL && line[0][0] == '\0')
	{
		ft_strdel(&save_rd[fd]);
		return (0);
	}
	save_rd[fd] = start_of_next_line(fd, buff_rd, save_rd);
	free(buff_rd);
	return (1);
}
