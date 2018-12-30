/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 05:01:21 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:33:58 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	get_lst_width(t_args *head)
{
	size_t ret;

	ret = 0;
	while (head)
	{
		if (ft_strlen(head->name) > ret)
			ret = ft_strlen(head->name);
		head = head->next;
	}
	return ((int)ret);
}

int	get_lst_height(t_args *head)
{
	int ret;

	ret = 0;
	while (head)
	{
		if (head->exist)
			ret++;
		head = head->next;
	}
	return (ret);
}

int	disp_check(t_args *head, struct winsize ws)
{
	int split;
	int height;
	int width;

	split = 1;
	width = get_lst_width(head);
	height = get_lst_height(head);
	while ((height / split) > ws.ws_row - 3 - 3 - 1 - 1)
		split++;
	if ((width + 2) * split > ws.ws_col)
		return (-1);
	else
		return (split);
}
