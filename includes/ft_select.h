/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 04:50:16 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/13 04:09:58 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include "libft.h"
# include <unistd.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>

# define KEY_UP				"\033[Am"
# define KEY_DOWN			"\033[Bm"
# define KEY_RIGHT			"\033[Cm"
# define KEY_LEFT			"\033[Dm"
# define KEY_DELETE			"\033[3~"
# define KEY_BACKSPACE		127
# define KEY_COLOR			126
# define KEY_RESIZE			-69
# define KEY_S_NONE			45
# define KEY_S_ALL			42
# define KEY_HIDE			36
# define KEY_SPACE			32
# define KEY_ESCAPE			27
# define KEY_RETURN			10
# define KEY_END			0

typedef struct		s_args
{
	char			*name;
	int				current;
	int				selected;
	int				exist;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

int					raw_term(void);
int					def_term(void);

int					lst_init(t_args **head, char **args);
#endif
