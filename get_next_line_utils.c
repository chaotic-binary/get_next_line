/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:30:56 by ttamesha          #+#    #+#             */
/*   Updated: 2020/05/27 13:07:53 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(char *content)
{
	t_list *elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
	{
		if (content)
			free(content);
		return (NULL);
	}
	elem->line = content;
	elem->next = NULL;
	return (elem);
}

size_t	ft_strlen(const char *str)
{
	const char *s;

	s = str;
	while (*s)
		++s;
	return (s - str);
}

char	*ft_strjoin_part(char *s1, char *s2)
{
	char	*new;
	char	*newptr;
	size_t	len;
	char	*n;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strchr(s2, '\n');
	len = n ? n - s2 + ft_strlen(s1) : ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	newptr = new;
	while (*s1)
		*newptr++ = *s1++;
	while (*s2 && *s2 != '\n')
		*newptr++ = *s2++;
	*newptr = '\0';
	return (new);
}

char	*ft_strdup(const char *src)
{
	char			*dub;
	char			*s;

	dub = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dub == NULL)
		return (NULL);
	s = dub;
	while (*src)
		*dub++ = *src++;
	*dub = '\0';
	return (s);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str != (char)c)
			++str;
		else
			return ((char *)str);
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}
