/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:55:58 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/11 14:04:46 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*mem;

	mem = (char *)malloc(sizeof(char) * size + 1);
	if (!mem)
		return (NULL);
	mem[size] = '\0';
	ft_bzero(mem, size);
	return (mem);
}
