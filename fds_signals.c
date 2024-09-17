/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:39:15 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/17 17:29:31 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_inner_shell_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

int	ft_heredoc_sig(int sig)
{
	static bool		end;	

	if (sig == SIGINT)
	{
		rl_done = 1;
		end = true;
	}
	if (sig == -2)
	{
		end = false;
		rl_event_hook = NULL;
		rl_done = 0;
	}
	if (end == true)
		return (FAILURE);
	return (SUCCESS);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = (void *)ft_heredoc_sig;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_set_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void	set_up_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = client_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
