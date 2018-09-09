/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:31:04 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/05 19:33:00 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcpy(char **tab)
{
	char	**ret;
	int		size;
	int		i;

	size = ft_strlen_tab(tab);
	i = -1;
	if ((ret = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return (NULL);
	while (++i < size)
		if ((ret[i] = ft_strdup(tab[i])) == NULL)
			return (NULL);
	ret[i] = NULL;
	return (ret);
}
