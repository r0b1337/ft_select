#include "ft_select.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
		clean_exit();
}

void	sigwinch_handler(int signo)
{
	char byte[2];

	if (signo == SIGWINCH)
	{
		byte[0] = KEY_RESIZE;
		byte[1] = KEY_END;
		ioctl(STDERR_FILENO, TIOCSTI, byte);
	}
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
}
