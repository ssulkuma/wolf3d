/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:03:50 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/29 14:22:11 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*link;

	if (!*alst)
		return ;
	link = *alst;
	while (link != NULL)
	{
		del(link->content, link->content_size);
		free(link);
		link = link->next;
	}
	*alst = NULL;
}
