#include "headers.h"

void	handle_signal_message(int signum, siginfo_t *siginfo, void *unused)
{
	static int	ascii = 0;
	static int	power = 0;

	(void)unused;
	if (signum == SIGUSR1)
		ascii += 1 << (7 - power);
	power += 1;
	if (power == 8)
	{
		if (g_flag == 1)
		{
			ft_putchar(ascii);
		}
		power = 0;
		ascii = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			handle_error("Error signal\n");
	}
}

int	main(int argc, char **argv)
{
	char				answer;
	struct sigaction	catch;

	(void)argv;
	if (argc != 1)
		handle_error("Error arguments\n");
	ft_putstr("🗿\033[1;33mShould server show messages❓\nY(Yes)/N(No): \033[0m");
	scanf("%c", &answer);
	if (answer == 'Y')
		g_flag = 1;
	else if (answer == 'N')
		g_flag = -1;
	else
		handle_error("Wrong input!\n");
	ft_putstr("🍻 \033[1;33mServer has started! 📣\n🔢 PID -> \033[0m");
	ft_putnbr(getpid());
	write(1, "\n", 1);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = handle_signal_message;
	if ((sigaction(SIGUSR1, &catch, 0)) == -1
		|| (sigaction(SIGUSR2, &catch, 0)) == -1)
		handle_error("Error sigaction\n");
	while (1)
		pause();
	return (0);
}
