/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:33:59 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/29 14:22:56 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;

	link = (t_list *)malloc(sizeof(t_list));
	if (!link)
		return (NULL);
	if (content == 0)
	{
		link->content = NULL;
		link->content_size = 0;
		link->next = NULL;
		return (link);
	}
	link->content = malloc(content_size);
	if (!link->content)
		return (NULL);
	ft_memmove(link->content, content, content_size);
	link->content_size = content_size;
	link->next = NULL;
	return (link);
}
