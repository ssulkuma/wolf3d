/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:02:25 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/05 17:38:26 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t ds)
{
	size_t		len_dest;
	size_t		len_src;
	size_t		res;
	size_t		i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	i = 0;
	if (ds > len_dest)
		res = len_dest + len_src;
	else
		res = len_src + ds;
	while (src[i] && (len_dest + 1) < ds)
	{
		dest[len_dest] = src[i];
		len_dest++;
		i++;
	}
	dest[len_dest] = '\0';
	return (res);
}
