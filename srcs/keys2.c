/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 02:47:24 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 03:05:12 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		press_enter(t_args **head, char *key)
{
	if (key[0] == KEY_RETURN && key[1] == KEY_END)
		return (send_ret(*head));
	else
		return (1);
}
