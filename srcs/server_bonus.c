#include "minitalk.h"

void	handler(int signal, siginfo_t *info, void *context)
{
	static int		bit;
	static int		c;

	(void)context;
	if (signal == SIGUSR2)
		c |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		if (c == 0)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	ft_printf("%u\n", getpid());
	if (sigaction(SIGUSR1, &sa, 0) == -1)
	{
		ft_printf("Signal error.\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, 0) == -1)
	{
		ft_printf("Signal error.\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
