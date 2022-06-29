/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:07:01 by ssulkuma          #+#    #+#             */
/*   Updated: 2021/11/15 17:51:50 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*only_whitespaces(void)
{
	char	*str;

	str = (char *)malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	s_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (i == s_len)
		return (only_whitespaces());
	while (s[s_len - 1] == ' ' || s[s_len - 1] == '\n' || s[s_len - 1] == '\t')
		s_len--;
	str = (char *)malloc(sizeof(char) * s_len - i + 1);
	if (!str)
		return (NULL);
	while (i < s_len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
