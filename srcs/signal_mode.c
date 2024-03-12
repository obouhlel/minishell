/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:33:11 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/12 18:49:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>

volatile int	g_signal;

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
