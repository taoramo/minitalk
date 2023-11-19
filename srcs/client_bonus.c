#include "minitalk.h"

int	ft_str_to_uint(const char *str)
{
	unsigned int	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] != 0 && str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

unsigned int	ft_atou(const char *str)
{
	int	i;

	i = 0;
	while (((str[i] == 32) || (str[i] > 8 && str[i] < 14)) && str[i] != 0)
	{
		i++;
	}
	if ((str[i] == 43 || str[i] == 45) && str[i] != 0)
	{
		if (str[i] == 45)
		{
			return (0);
		}
		i++;
	}
	return (ft_str_to_uint(&str[i]));
}

int	str_to_sig(pid_t pid, char *s)
{
	int				i;
	int				j;
	unsigned char	b;

	i = 0;
	j = 0;
	while (i <= (int)ft_strlen(s))
	{
		b = 0;
		j = 0;
		while (j < 8)
		{
			b = s[i] >> j;
			if (1 & b)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			j++;
			usleep(100);
		}
		i++;
	}
	return (1);
}

void	clihandler(int i, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (i == 30)
	{
		ft_printf("Message delivered.\n");
		exit(0);
	}
	else
		ft_printf("Error.\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sacli;

	sacli.sa_sigaction = clihandler;
	sigemptyset(&sacli.sa_mask);
	sacli.sa_flags = 0;
	sigaction(SIGUSR1, &sacli, 0);
	if (argc != 3 || ft_atou(argv[1]) == 0)
	{
		ft_printf("Invalid arguments.\n");
		return (1);
	}
	str_to_sig(ft_atou(argv[1]), argv[2]);
	while (1)
	{
		sleep(1000);
		ft_printf("Timeout.\n");
		exit(1);
	}
}
