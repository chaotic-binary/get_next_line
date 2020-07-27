/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 01:29:58 by ttamesha          #+#    #+#             */
/*   Updated: 2020/05/27 13:27:01 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "unistd.h"
# include "stdlib.h"

int						get_next_line(const int fd, char **line);

typedef struct			s_list
{
	char				*line;
	struct s_list		*next;
}						t_list;

t_list					*ft_lstnew(char *content);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *src);
char					*ft_strjoin_part(char *s1, char *s2);
char					*ft_strchr(const char *str, int c);

#endif
