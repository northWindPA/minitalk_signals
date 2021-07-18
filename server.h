#ifndef SERVER_H
# define SERVER_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>

void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	handle_error(char *str);

void	handle_signal_message(int signum, siginfo_t *siginfo, void *unused);

#endif