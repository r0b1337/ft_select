#include "ft_select.h"

int	move_down(t_args **head)
{
	t_args *tmp;

	tmp = *head;
	if (tmp->next == NULL)
		return (-1);
	while (tmp && !tmp->current)
		tmp = tmp->next;
	tmp->current = 0;
	if (!tmp->next)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->current = 1;
	}
	else
		tmp->next->current = 1;
	return (1);
}

int	move_up(t_args **head)
{
	t_args *tmp;

	tmp = *head;
	if (tmp->next == NULL)
		return (-1);
	while (tmp && !tmp->current)
		tmp = tmp->next;
	tmp->current = 0;
	if (!tmp->prev)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->current = 1;
	}
	else
		tmp->prev->current = 1;
	return (1);
}

int	toggle_arg(t_args **head)
{
	t_args *tmp;
	
	tmp = *head;
	if (tmp->next == NULL)
		return (-1);
	while (tmp && !tmp->current)
		tmp = tmp->next;
	if (tmp->selected == 0)
		tmp->selected = 1;
	else
		tmp->selected = 0;
	move_down(head);
	return (1);
}
