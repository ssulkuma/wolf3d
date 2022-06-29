/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:14:31 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/29 19:13:49 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*mem;
	t_list	*new;
	t_list	*temp;
	t_list	*head;

	new = NULL;
	temp = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		mem = (t_list *)malloc(sizeof(t_list));
		if (!mem)
			return (NULL);
		mem = f(lst);
		new = mem;
		if (temp == NULL)
			head = new;
		else
			temp->next = new;
		free(mem);
		temp = new;
		lst = lst->next;
	}
	return (head);
}
