/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:44:51 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/03 17:02:24 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	a;
	size_t			i;

	s = (unsigned char *)str;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == a)
			return (&s[i]);
		i++;
	}
	return (0);
}
