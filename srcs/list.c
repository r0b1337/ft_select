/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 02:20:32 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:14:17 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	lst_add(t_args *head, char *name)
{
	t_args	*new_node;
	t_args	*tmp;

	tmp = head;
	if (!(new_node = malloc(sizeof(t_args))) 
			|| !(new_node->name = ft_strdup(name)))
		return (-1);
	new_node->current = 0;
	new_node->selected = 0;
	new_node->exist = 1;
	new_node->next = NULL;
	if (head->next == NULL)
	{
		head->next = new_node;
		new_node->prev = head;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
	return (1);
}

int			lst_init(t_args **head, char **args)
{
	t_args	*tmp;
	int		i;

	i = 1;
	tmp = *head;
	if (!(tmp = malloc(sizeof(t_args))) 
			|| !(tmp->name = ft_strdup(args[1])))
		return (-1);
	tmp->current = 1;
	tmp->selected = 0;
	tmp->exist = 1;
	tmp->prev = NULL;
	tmp->next = NULL;
	while (args[++i])
		if (lst_add(tmp, args[i]) == -1)
			return (-1);
	*head = tmp;
	return (1);
}

t_args	*get_curr(t_args **head)
{
	t_args *ret;

	ret = *head;
	if (!ret->next)
		return (NULL);
	while (ret->next && (!ret->current || !ret->exist))
			ret = ret->next;
	return (ret);
}

int		send_ret(t_args **head)
{
	t_args *tmp;

	tmp = *head;
	if (!tmp)
		return (-1);
	while (tmp)
	{
		if (tmp->selected)
		{
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	clean_exit();
	return (1);
}
