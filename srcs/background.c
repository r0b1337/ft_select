/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 05:01:21 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:33:58 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	disp_title(struct winsize ws)
{
	char	*title_content;
	int		x;
	int		y;

	if (!(title_content = ft_strdup("-+- ft_select -+-")))
		return (EXIT_FAILURE);
	x = (ws.ws_col / 2) - (ft_strlen(title_content) / 2);
	y = 1;
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, &tc_putc);
	ft_putstr_fd(FG_BLACK, STDERR_FILENO);
	ft_putstr_fd(BG_WHITE, STDERR_FILENO);
	ft_putstr_fd(title_content, STDERR_FILENO);
	ft_putstr_fd(BG_RESET, STDERR_FILENO);
	ft_putstr_fd(FG_RESET, STDERR_FILENO);
	ft_strdel(&title_content);
	return (EXIT_SUCCESS);
}

/*
**	------------------------------------------------------------------------- +
**	disp_keys() displays informations at the bottom of the screen.
**	------------------------------------------------------------------------- +
*/

static int	disp_keys(struct winsize ws)
{
	char *keys_content;

	if (!(keys_content = ft_strdup("-- [ARROWS] move -- [SPACE] select -- [DEL] delete -- [ESC] quit -- [RETURN] send list --")))
			return (EXIT_FAILURE);
	if (ws.ws_col < ft_strlen(keys_content))
	{
		ft_strdel(&keys_content);
		return (EXIT_FAILURE);
	}
	else
	{
		tputs(tgoto(tgetstr("cm", NULL), ws.ws_col / 2 - ft_strlen(keys_content) / 2, ws.ws_row - 2), STDERR_FILENO, tc_putc);
		ft_putstr_fd(BG_WHITE, STDERR_FILENO);
		ft_putstr_fd(FG_BLACK, STDERR_FILENO);
		ft_putendl_fd(keys_content, STDERR_FILENO);
		ft_strdel(&keys_content);
		ft_putstr_fd(FG_RESET, STDERR_FILENO);
		ft_putstr_fd(BG_RESET, STDERR_FILENO);
		return (EXIT_SUCCESS);
	}
}

/*
**	------------------------------------------------------------------------- +
**	disp_rows() displays a bar at the top (header) & bottom of the screen.
**	------------------------------------------------------------------------- +
*/

static void	disp_rows(struct winsize ws, int i)
{
	int	j;

	j = 0;
	while (j < ws.ws_col)
	{
		tputs(tgoto(tgetstr("cm", NULL), j, i), 1, &tc_putc);
		ft_putstr_fd(BG_WHITE, STDERR_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
		ft_putstr_fd(BG_RESET, STDERR_FILENO);
		j++;
	}
}

/*
**	------------------------------------------------------------------------- +
**	disp_back() displays a background for ft_select.
**	------------------------------------------------------------------------- +
*/

void		disp_back(struct winsize ws)
{
	int	i;

	i = 0;
	while (i < ws.ws_row)
	{
		if (i == 0 || i == 1 || i == 2 ||
				i == ws.ws_row - 1 || i == ws.ws_row - 2 || i == ws.ws_row - 3)
			disp_rows(ws, i);
		i++;
	}
	disp_title(ws);
	disp_keys(ws);
}
