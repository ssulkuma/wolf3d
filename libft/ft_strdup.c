/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:13:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/10/29 14:48:00 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		l;
	char	*dest;

	i = 0;
	l = 0;
	while (src[l] != '\0')
		l++;
	dest = (char *)malloc(sizeof(*src) * (l + 1));
	if (src == NULL || dest == NULL)
		return (NULL);
	while (i <= l)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
