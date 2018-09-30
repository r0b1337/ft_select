/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 04:18:42 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:35:47 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		free_list(t_args **head)
{
	t_args *tmp;
	t_args *curr;

	curr = *head;
	if (!curr)
		return (-1);
	while (curr)
	{
		ft_strdel(&curr->name);
		if (curr->prev)
			curr->prev = NULL;
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	return (1);
}
