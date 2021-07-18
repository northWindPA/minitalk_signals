#include "headers.h"

void	sig_msg_output(int pid, int *array)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((array[i] % 2) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				handle_error("Error signal!\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				handle_error("Error signal!\n");
		}
		i++;
		usleep(50);
	}
}

void	make_array(char ascii, int pid)
{
	int	i;
	int	*array;

	array = malloc(sizeof(int) * 8);
	if (array == NULL)
		handle_error("Malloc error");
	i = 0;
	while (i < 8)
	{
		array[i] = 0;
		i++;
	}
	i--;
	while (i != -1)
	{
		array[i] = ascii;
		ascii /= 2;
		i--;
	}
	sig_msg_output(pid, array);
	free(array);
}

int	handle_message(int server_pid, char *message)
{
	int		i;

	i = 0;
	message = ft_strjoin(message, "\n");
	while (message[i])
	{
		make_array(message[i], server_pid);
		i++;
	}
	free(message);
	return (0);
}

void	handle_signal(int signum, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)siginfo;
	(void)signum;
}

int	main(int argc, char **argv)
{
	struct sigaction	catch;

	if (argc == 3)
	{
		catch.sa_flags = SA_SIGINFO;
		catch.sa_sigaction = handle_signal;
		if ((sigaction(SIGUSR2, &catch, 0)) == -1)
			handle_error("Error sigaction\n");
		ft_putstr("📶 \033[1;33mSignal has been received! 👍🏽\n\033[0m");
		handle_message(ft_atoi(argv[1]), argv[2]);
	}
	else
		handle_error("Error arguments\n");
	return (0);
}
