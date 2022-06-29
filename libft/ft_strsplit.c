/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:52:14 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/03/14 16:01:36 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	w_count(char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			n++;
		i++;
	}
	return (n);
}

static size_t	w_len(char const *s, char c)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i++;
			l++;
		}
		else
			return (l);
	}
	return (l);
}	

static char	**free_all(char	**mem, size_t	j)
{
	while (j >= 0)
	{
		free(mem[j]);
		j--;
	}
	free(mem);
	return (NULL);
}

static char	**set_splits(char const *s, char c, char **mem, size_t i)
{
	size_t	j;
	size_t	n;
	size_t	len;

	j = 0;
	while (j < w_count(s, c))
	{
		n = 0;
		len = w_len(&s[i], c);
		mem[j] = malloc(sizeof(char) * (len + 1));
		if (!mem[j])
		{
			free_all(mem, j - 1);
			return (NULL);
		}
		while (n < len)
			mem[j][n++] = s[i++];
		mem[j][n] = '\0';
		while (s[i] == c && s[i] != '\0')
			i++;
		j++;
	}
	mem[j] = NULL;
	return (mem);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**mem;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	mem = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1));
	if (!mem)
		return (NULL);
	while (s[i] == c)
		i++;
	set_splits(s, c, mem, i);
	return (mem);
}
