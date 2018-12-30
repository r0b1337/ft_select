/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 04:50:16 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/30 04:24:44 by rdurst           ###   ########.fr       */
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
# define KEY_BACKSPACE			127
# define KEY_COLOR			126
# define KEY_RESIZE			-69
# define KEY_S_NONE			45
# define KEY_S_ALL			42
# define KEY_HIDE			36
# define KEY_SPACE			32
# define KEY_ESCAPE			27
# define KEY_RETURN			10
# define KEY_END			0

# define BG_BLUE			"\033[104m"
# define BG_GREEN			"\033[102m"
# define BG_WHITE			"\033[47m"
# define BG_RESET			"\033[49m"

struct termios orig_termios;

typedef struct		s_args
{
	char			*name;
	int				current;
	int				selected;
	int				exist;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

void					raw_term(void);
void					def_term(void);

int					lst_init(t_args **head, char **args);
t_args				*get_curr(t_args **head);
int				ft_lstlen(t_args *head);
int					send_ret(t_args *head);

int					get_lst_height(t_args *head);
int					get_lst_width(t_args *head);
int					disp_check(t_args *head, struct winsize ws);

int					free_list(t_args **head);

int					move_down(t_args **head);
int					move_up(t_args **head);
int					toggle_arg(t_args **head);
int					del_arg(t_args **head);

int					press_up(t_args **head, char *key);
int					press_down(t_args **head, char *key);
int					press_space(t_args **head, char *key);
int					press_delete(t_args **head, char *key);
int					press_escape(t_args **head, char *key);
int					press_enter(t_args **head, char *key);

void					sigint_handler(int signo);
void					sigwinch_handler(int signo);
void					signal_handler(void);

void					clean(void);
void					clean_exit(void);
#endif
