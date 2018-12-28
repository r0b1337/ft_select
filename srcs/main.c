/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 05:01:21 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:33:58 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	clean_exit(void)
{
	def_term();
	exit(EXIT_SUCCESS);
}

int	tc_putc(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void		raw_term(void)
{
	char			*term_type;
	struct termios		raw;

	tcgetattr(STDERR_FILENO, &orig_termios);
	raw = orig_termios;
	if (!(term_type = getenv("TERM")))
	{
		ft_putendl_fd("couldn't reach 'TERM' environement variable.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (tgetent(NULL, term_type) == -1)
	{
		ft_putendl_fd("couldn't find terminal in the termcap database.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	raw.c_lflag &= ~ECHO;
	raw.c_lflag &= ~ICANON;
	raw.c_lflag &= ~OPOST;
	raw.c_cc[VTIME] = 0;
	raw.c_cc[VMIN] = 1;
	tcsetattr(STDERR_FILENO, TCSADRAIN, &raw);
	tputs(tgetstr("vi", NULL), STDERR_FILENO, tc_putc);
	tputs(tgetstr("ti", NULL), STDERR_FILENO, tc_putc);
}

void		def_term(void)
{
	tcsetattr(STDERR_FILENO, TCSADRAIN, &orig_termios);
	tputs(tgetstr("ve", NULL), STDERR_FILENO, tc_putc);
	tputs(tgetstr("te", NULL), STDERR_FILENO, tc_putc);
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
	while (++y < 3)
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

void		disp_args(t_args *head)
{
	int i;
	int indent;
	struct winsize ws;

	i = 4;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &ws);
	indent = 2;
	tputs(tgoto(tgetstr("cm", NULL), indent, i), STDERR_FILENO, tc_putc);
	if (head->next == NULL)
		ft_putstr(head->name);
	else
	{	
		while (head)
		{
			if (head->exist)
			{
				tputs(tgoto(tgetstr("cm", NULL), indent, i++), STDERR_FILENO, tc_putc);
				if (head->current == 1)
					tputs(tgetstr("us", NULL), STDERR_FILENO, tc_putc);
				if (head->selected == 1)
					tputs(tgetstr("so", NULL), STDERR_FILENO, tc_putc);
				ft_putstr_fd(head->name, STDERR_FILENO);
				tputs(tgetstr("ue", NULL), STDERR_FILENO, tc_putc);
				tputs(tgetstr("se", NULL), STDERR_FILENO, tc_putc);
			}
			head = head->next;
		}
	}
	return ;
}

int		ft_select(t_args **head)
{
	int	ret;
	char	buf[5];
	while (1)
	{
		signal(SIGINT, sigint_handler);
		clean();
		disp_rows();
		disp_args(*head);
		ret = read(STDERR_FILENO, buf, 4);
		buf[ret] = '\0';
		press_up(head, buf);
		press_down(head, buf);
		press_space(head, buf);
		press_delete(head, buf);
		press_escape(head, buf);
		press_enter(head, buf);
	}
	return (1);
}

void		clean(void)
{
	tputs(tgetstr("cl", NULL), STDERR_FILENO, tc_putc);
}

int		main(int ac, char **av)
{
	t_args			*head;

	if (ac < 2)
	{
		ft_putendl_fd("Usage : './ft_select <files...>'", STDERR_FILENO);
		return (-1);
	}
	raw_term();
	head = NULL;
	lst_init(&head, av);
	ft_select(&head);
	return (0);
}
