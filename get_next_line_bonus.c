/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:48:14 by ttamesha          #+#    #+#             */
/*   Updated: 2020/05/27 14:38:14 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*get_rem(t_list **start, int fd)
{
	t_list		*tmp;

	if (!*start)
	{
		*start = ft_lstnbnew(fd, ft_strdup(""));
		if (!*start || ((*start)->line == NULL))
			return (NULL);
		return (*start);
	}
	tmp = *start;
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	tmp->next = ft_lstnbnew(fd, ft_strdup(""));
	if (!(tmp->next) || ((tmp->next)->line == NULL))
		return (NULL);
	return (tmp->next);
}

static void		free_fd(t_list **start, int fd)
{
	t_list *pre;
	t_list *tmp;

	if (!*start)
		return ;
	pre = *start;
	while (pre->next && pre->fd != fd && pre->next->fd != fd)
		pre = pre->next;
	tmp = (pre == *start) ? *start : pre->next;
	if (tmp->fd == fd)
	{
		if (tmp->line)
		{
			free(tmp->line);
			tmp->line = NULL;
		}
		if (tmp == *start)
			*start = (*start)->next;
		else
			pre->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

static void		set_rem(t_list **start, t_list **lst, char *rem)
{
	if (!*lst || !*start)
		return ;
	if ((*lst)->line)
	{
		free((*lst)->line);
		(*lst)->line = NULL;
		if (rem)
			(*lst)->line = ft_strdup(rem);
	}
	if (!((*lst)->line))
		free_fd(start, (*lst)->fd);
}

static int		get_line(t_list **start, t_list **lst, char **line, char *rem)
{
	char *n;
	char *tmp;

	tmp = *line;
	*line = ft_strjoin_part(tmp, rem);
	if (tmp)
		free(tmp);
	if (!*line)
	{
		free_fd(start, (*lst)->fd);
		return (-1);
	}
	n = ft_strchr(rem, '\n');
	if (n)
	{
		tmp = ft_strdup(n + 1);
		set_rem(start, lst, tmp);
		if (tmp)
			free(tmp);
	}
	if (!n && *((*lst)->line))
		set_rem(start, lst, "");
	if (!(*lst))
		return (-1);
	return (n ? 1 : 0);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*start;
	t_list			*rem;
	char			buff[BUFFER_SIZE + 1];
	int				rd;
	int				n;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	if ((rem = get_rem(&start, fd)) && *(rem->line))
		if ((n = get_line(&start, &rem, line, rem->line)) != 0)
			return (n);
	while (rem && (rd = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if ((n = get_line(&start, &rem, line, buff)) != 0)
			return (n);
	}
	if ((rem && rd == 0 && *(rem->line) == '\0') || (rd < 0))
	{
		free_fd(&start, fd);
		return (rd);
	}
	return (-1);
}
