#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

void	ft_putstr(char *str);
void	handle_error(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(const char *string);
char	*ft_strjoin(char const *s1, char const *s2);

void	make_array(char ascii, int pid);
void	sig_msg_output(int pid, int *array);
int		handle_message(int server_pid, char *message);
void	handle_signal(int signum, siginfo_t *siginfo, void *unused);

#endif
