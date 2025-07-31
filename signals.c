/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:47:44 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/23 18:12:54 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_handler(int sig)
{
	(void)sig;
	printf("Quit (core dumped)");
	printf("\n");
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_number = sig;
	printf("\n");
	if ((isatty(STDIN_FILENO) && rl_readline_state & RL_STATE_READCMD))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	prepare_signals(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	sigemptyset(&sa_int->sa_mask);
	sa_int->sa_flags = 0;
	sa_int->sa_handler = handle_sigint;
	sigaction(SIGINT, sa_int, NULL);
	sigemptyset(&sa_quit->sa_mask);
	sa_quit->sa_flags = 0;
	sa_quit->sa_handler = SIG_IGN; 
	sigaction(SIGQUIT, sa_quit, NULL);
}
