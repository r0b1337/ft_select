#include "ft_select.h"

int		move_down(t_args **head)
{
	t_args *tmp;

	if (!(tmp = get_curr(head)))
		return (-1);
	tmp->current = 0;
	if (!tmp->next)
	{
		while (tmp->prev)
			tmp = tmp->prev;
	}
	else
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->exist)
		{
			tmp->current = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		move_up(t_args **head)
{
	t_args *tmp;

	if (!(tmp = get_curr(head)))
		return (-1);
	tmp->current = 0;
	if (!tmp->prev)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	else
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->exist)
		{
			tmp->current = 1;
			break;
		}
		tmp = tmp->prev;
	}
	return (1);
}

int		toggle_arg(t_args **head)
{
	t_args *tmp;

	if (!(tmp = get_curr(head)))
		return (-1);
	if (tmp->selected == 0)
		tmp->selected = 1;
	else
		tmp->selected = 0;
	move_down(head);
	return (1);
}

int		del_arg(t_args **head)
{
	t_args *tmp;

	if (!(tmp = get_curr(head)))
		return (-1);
	move_down(head);
	tmp->exist = 0;
	return (1);
}
