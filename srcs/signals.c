/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:33:11 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/12 18:44:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>

volatile int	g_signal;

void	block_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

void	unblock_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
}

void	handler_quit(int signal)
{
	if (signal != SIGQUIT)
	{
		block_signal(SIGQUIT);
		return ;
	}
	ft_putstr_fd("Quit", STDERR);
}

void	handler_end_spe(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR);
		// ctrl_c_heredoc((t_heredoc){NULL, NULL, 0}, NULL, DESTROY);
		exit(130);
	}
}

void	handler_end(int signal)
{
	if (signal == SIGINT)
	{
		if (g_signal == 0 || g_signal == 2)
		{
			block_signal(SIGINT);
			g_signal = 2;
			rl_on_new_line();
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
			unblock_signal(SIGINT);
		}
		else
			g_signal = 0;
	}
}

static
void	mode_signal_bis(int mode)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	if (mode == S_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == S_HEREDOC)
	{
		act.sa_handler = &handler_end_spe;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	mode_signal(int mode)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	if (mode == S_MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
		act.sa_handler = &handler_end;
		act.sa_flags = 0;
		sigaction(SIGINT, &act, NULL);
	}
	if (mode == S_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
		mode_signal_bis(mode);
}
