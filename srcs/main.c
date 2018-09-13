/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 05:01:21 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/13 04:11:04 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		raw_term(void)
{
	char			*term_type;
	struct termios	s_term;

	if (!(term_type = getenv("TERM")))
	{
		ft_putendl("couldn't reach 'TERM' environement variable.");
		return (0);
	}
	if (tgetent(NULL, term_type) == -1)
	{
		ft_putendl("couldn't find terminal in the termcap database.");
		return (0);
	}
	tcgetattr(0, &s_term);
	s_term.c_lflag &= ~ECHO;
	s_term.c_lflag &= ~ICANON;
	s_term.c_lflag &= ~OPOST;
	s_term.c_cc[VTIME] = 0;
	s_term.c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSADRAIN, &s_term) == -1)
		return (0);
	return (1);
}

int		def_term(void)
{
	char			*term_type;
	struct termios	s_term;

	if (!(term_type = getenv("TERM")))
	{
		ft_putendl("couldn't reach 'TERM' environement variable.");
		return (0);
	}
	if (tgetent(NULL, term_type) == -1)
	{
		ft_putendl("couldn't find terminal in the termcap database.");
		return (0);
	}
	tcgetattr(0, &s_term);
	s_term.c_lflag |= ~ECHO;
	s_term.c_lflag |= ~ICANON;
	s_term.c_lflag |= ~OPOST;
	s_term.c_cc[VTIME] = 0;
	s_term.c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSADRAIN, &s_term) == -1)
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	t_args			*head;

	if (ac < 2)
	{
		ft_putendl("Usage : './ft_select <files...>'");
		return (-1);
	}
	if (!raw_term())
		return (0);
	head = NULL;
	lst_init(&head, av);
	if (!def_term())
		return (0);
	return (0);
}
