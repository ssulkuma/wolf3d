/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:11:11 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/10 17:02:53 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	chr;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	chr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == chr)
			return (dest + 1 + i);
		i++;
	}
	return (NULL);
}
