/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:54:12 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/11 18:13:07 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*mem;

	i = 0;
	if (!s)
		return (NULL);
	mem = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!mem)
		return (NULL);
	if (s[i] != '\0' && *f != NULL)
	{
		while (s[i])
		{
			mem[i] = f(s[i]);
			i++;
		}
	}
	mem[i] = '\0';
	return (mem);
}
