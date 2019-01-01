/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 05:01:21 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:33:58 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	disp_error(struct winsize ws)
{
	char	*error_content;
	int		x;
	int		y;

	y = -1;
	clean();
	ft_putstr_fd(BG_BLUE, STDERR_FILENO);
	if (ws.ws_col <= 24 || ws.ws_row <= 7)
		return (EXIT_FAILURE);
	while (++y < ws.ws_row)
	{
		x = -1;
		while (++x < ws.ws_col)
		{
			tputs(tgoto(tgetstr("cm", NULL), x, y), 1, &tc_putc);
			ft_putchar_fd(' ', STDERR_FILENO);
		}
	}
	if (!(error_content = ft_strdup("screen size is too small")))
		return (EXIT_FAILURE);
	x = (ws.ws_col / 2) - (ft_strlen(error_content) / 2);
	y = ws.ws_row / 2;
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, &tc_putc);
	ft_putstr_fd(error_content, STDERR_FILENO);
	ft_putstr_fd(BG_RESET, STDERR_FILENO);
	ft_strdel(&error_content);
	return (EXIT_SUCCESS);
}

void		disp_rows(void)
{
	struct winsize	ws;
	int		x;
	int		y;

	x = -1;
	y = -1;
	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		ft_putendl_fd("SCREEN SIZE IS TOO SMALL", STDERR_FILENO);
		return ;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), STDERR_FILENO, tc_putc);
	ft_putstr_fd(BG_WHITE, STDERR_FILENO);
	while(++y < 3)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, y), STDERR_FILENO, tc_putc);
		while (++x < ws.ws_col)
			write(STDERR_FILENO, " ", 1);
		x = -1;
	}
	y = -1;
	while (++y <= 3)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, ws.ws_row - y), STDERR_FILENO, tc_putc);
		while (++x < ws.ws_col)
			write(STDERR_FILENO, " ", 1);
		x = -1;
	}
	ft_putstr_fd(BG_RESET, STDERR_FILENO);
	return ;
}

void		disp_args(t_args *head, struct winsize ws)
{
	int x;
	int y;
	int cols;
	t_args *tmp;

	x = 2;
	y = 4;
	tmp = head;
	tputs(tgoto(tgetstr("cm", NULL), x, y), STDERR_FILENO, tc_putc);
	cols = disp_check(head, ws);
	if (tmp->next == NULL)
		ft_putstr_fd(tmp->name, STDERR_FILENO);
	else
	{	
		while (tmp)
		{	
			if (tmp->exist)
			{
				if (y - 4 == get_lst_height(head) / cols)
				{
					y = 4;
					x = x + get_lst_width(head) + 2;
				}
				tputs(tgoto(tgetstr("cm", NULL), x, y++), STDERR_FILENO, tc_putc);
				if (tmp->current == 1)
					tputs(tgetstr("us", NULL), STDERR_FILENO, tc_putc);
				if (tmp->selected == 1)
					tputs(tgetstr("so", NULL), STDERR_FILENO, tc_putc);
				ft_putstr_fd(tmp->name, STDERR_FILENO);
				tputs(tgetstr("ue", NULL), STDERR_FILENO, tc_putc);
				tputs(tgetstr("se", NULL), STDERR_FILENO, tc_putc);
			}
			tmp = tmp->next;
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return ;
}
