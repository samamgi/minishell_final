/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:59:21 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:59:24 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle(int s)
{
	if (s == 2 && g_signal != -2)
	{
		g_signal = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	file_end(char *str, t_vars *va)
{
	free_tab(va->envi);
	close (va->fd[0]);
	close (va->fd[1]);
	close (va->fd[2]);
	free(str);
	printf("exit\n");
	exit (va->last_code);
}

void	end_heredoc(int s)
{
	(void)s;
	g_signal = 130;
	close(0);
}
