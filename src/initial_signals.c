/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:26:57 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 21:32:51 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_signal(int signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	initial_signals()
{
	signal(SIGINT, ctrl_c_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	modify_termios(struct termios *tios)
{
	tios->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}

void	reset_termios(struct termios *tios)
{
	tios->c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}
