/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:13:30 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/14 10:20:00 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void		mode_signal(int mode);

// SIGNAL
void		block_signal(int signal);
void		unblock_signal(int signal);
void		handler_quit(int signal);
void		handler_end_heredoc(int signal);
void		handler_end(int signal);

#endif