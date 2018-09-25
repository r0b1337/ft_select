#include "ft_select.h"

int	press_up(t_args **head, char *key)
{
	if (ft_memcmp(key, KEY_UP, ft_strlen(key)) == 0
			|| ft_memcmp(key, KEY_LEFT, ft_strlen(key)) == 0)
		return(move_up(head));
	else
		return (0);
}

int	press_down(t_args **head, char *key)
{
	if (ft_memcmp(key, KEY_DOWN, ft_strlen(key)) == 0
			|| ft_memcmp(key, KEY_RIGHT, ft_strlen(key)) == 0)
		return(move_down(head));
	else
		return (0);
}

int	press_space(t_args **head, char *key)
{
	if (key[0] == KEY_SPACE && key[1] == KEY_END)
		return(toggle_arg(head));
	else
		return (0);
}
