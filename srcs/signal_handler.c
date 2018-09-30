#include "ft_select.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
		clean_exit();
}
