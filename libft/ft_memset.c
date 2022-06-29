/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:13:33 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/02 15:38:07 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int val, size_t len)
{
	size_t			i;
	unsigned char	c;
	char			*str1;

	c = (unsigned char)val;
	str1 = (char *)str;
	i = 0;
	while (i < len)
	{
		str1[i] = c;
		i++;
	}
	return (str);
}
