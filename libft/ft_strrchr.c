/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:33:21 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/07 11:23:33 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	char	c;
	size_t	len;

	c = (char)chr;
	len = ft_strlen(str);
	while (str[len] != c && len > 0)
		len--;
	if (str[len] == c)
		return ((char *)&str[len]);
	return (NULL);
}
