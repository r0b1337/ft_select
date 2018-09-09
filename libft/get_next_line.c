/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 05:59:50 by rdurst            #+#    #+#             */
/*   Updated: 2018/03/18 16:26:27 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_return(int pos, t_list **memory)
{
	char	*tmp;

	if ((*memory)->content && (pos <= (int)ft_strlen((*memory)->content)
				&& ft_strlen((*memory)->content)))
	{
		if (pos == (int)ft_strlen((*memory)->content))
			(*memory)->content = NULL;
		else
		{
			tmp = (*memory)->content;
			if (!((*memory)->content = ft_strdup(ft_strchr(tmp, '\n') + 1)))
				return (-1);
			ft_strdel(&tmp);
		}
		return (1);
	}
	else
	{
		(*memory)->content = NULL;
		(*memory)->content_size = -1;
	}
	return (0);
}

static int			ft_read(char **unused, int fd)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = *unused;
		if (!(*unused = ft_strjoin(tmp, buf)))
			return (-1);
		ft_strdel(&tmp);
		if (ft_strchr(buf, '\n') != NULL || ret < BUFF_SIZE)
			break ;
	}
	return (1);
}

static t_list		*find_fd(int fd, t_list **memory)
{
	t_list	*tmp;

	tmp = *memory;
	while (tmp)
	{
		if (tmp->content_size == (size_t)fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!tmp)
	{
		if ((tmp = ft_lstnew(NULL, 0)) == NULL)
			return (NULL);
		if (!(tmp->content = ft_strdup("")))
			return (NULL);
		tmp->content_size = fd;
		ft_lstadd(memory, tmp);
		tmp = *memory;
	}
	return (tmp);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*actual_fd = NULL;
	t_list			*memory;
	int				pos;

	pos = 0;
	if (read(fd, NULL, 0) == -1 || BUFF_SIZE < 0 || line == NULL)
		return (-1);
	if ((memory = find_fd(fd, &actual_fd)) == NULL)
		return (-1);
	if (memory->content && ft_read((char **)&(memory->content), fd) == -1)
		return (-1);
	if (memory->content &&
			(pos = ft_strucpy(line, memory->content, '\n')) == -1)
		return (-1);
	return (ft_return(pos, &memory));
}
