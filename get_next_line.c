/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:48:14 by ttamesha          #+#    #+#             */
/*   Updated: 2020/05/27 14:37:57 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_rem(t_list **lst)
{
	if (!*lst)
	{
		*lst = ft_lstnew(ft_strdup(""));
		if (!*lst || ((*lst)->line == NULL))
			return (NULL);
	}
	if (*lst)
		return (*lst);
	return (NULL);
}

static void		set_rem(t_list **lst, char *rem)
{
	if (!*lst)
		return ;
	if ((*lst)->line)
	{
		free((*lst)->line);
		(*lst)->line = NULL;
		if (rem)
			(*lst)->line = ft_strdup(rem);
	}
	if (!((*lst)->line))
	{
		free(*lst);
		*lst = NULL;
	}
}

static int		get_line(t_list **lst, char **line, char *rem)
{
	char *n;
	char *tmp;

	tmp = *line;
	*line = ft_strjoin_part(tmp, rem);
	if (tmp)
		free(tmp);
	if (!*line)
	{
		set_rem(lst, NULL);
		return (-1);
	}
	n = ft_strchr(rem, '\n');
	if (n)
	{
		tmp = ft_strdup(n + 1);
		set_rem(lst, tmp);
		if (tmp)
			free(tmp);
	}
	if (!n && *((*lst)->line))
		set_rem(lst, "");
	if (!(*lst))
		return (-1);
	return (n ? 1 : 0);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*lst;
	char			buff[BUFFER_SIZE + 1];
	int				rd;
	int				n;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	if (get_rem(&lst) && *(lst->line))
		if ((n = get_line(&lst, line, lst->line)) != 0)
			return (n);
	while (lst && (rd = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if ((n = get_line(&lst, line, buff)) != 0)
			return (n);
	}
	if ((lst && rd == 0 && *(lst->line) == '\0') || (rd < 0))
	{
		set_rem(&lst, NULL);
		return (rd);
	}
	return (-1);
}
