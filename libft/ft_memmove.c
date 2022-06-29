/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:20:57 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/10 15:00:59 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (!s && !d)
		return (NULL);
	if (s < d)
	{
		while (i < len)
		{
			d[len - i - 1] = s[len - i - 1];
			i++;
		}
	}
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
