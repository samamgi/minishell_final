/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:39:41 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:39:42 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_pipes(t_vars *va, int *here_pipe)
{
	close(va->fd[0]);
	close(va->fd[1]);
	close(va->fd[2]);
	close(here_pipe[1]);
	close(here_pipe[0]);
}

static int	close_heredoc(char **line, char *limiter, t_vars *va,
		int here_pipe[2])
{
	if (g_signal == 130)
	{
		free_tab(va->envi);
		free(line[0]);
		free(limiter);
		close_pipes(va, here_pipe);
		exit(1);
	}
	if (line[0] == NULL)
	{
		ft_printf(2, "minishell: detecting end of file. close heredoc "
			"wanted '%s'\n", limiter);
		return (-1);
	}
	if (ft_strncmp(line[0], limiter, ft_strlen(limiter) + 1) == 0)
		return (-1);
	return (0);
}

static void	fill_doc(t_vars *va, t_list *lst, char *limiter, int here_pipe[2])
{
	char	*line[2];

	signal(SIGINT, &end_heredoc);
	lst_close(lst);
	free_lst(lst);
	while (1)
	{
		line[0] = readline("> ");
		if (close_heredoc(line, limiter, va, here_pipe) == -1)
			break ;
		line[1] = str_clr(va, line[0]);
		ft_putstr_fd(line[1], here_pipe[1]);
		ft_putstr_fd("\n", here_pipe[1]);
		free(line[1]);
	}
	free_tab(va->envi);
	free(limiter);
	close_pipes(va, here_pipe);
	if (line[0])
		free(line[0]);
	exit(0);
}

int	heredoc(t_vars *va, t_list *lst, char *limiter)
{
	int	here_pipe[2];
	int	pid;

	pipe(here_pipe);
	lst->fd_in = here_pipe[0];
	g_signal = -2;
	pid = fork();
	if (pid == 0)
		fill_doc(va, lst, limiter, here_pipe);
	free(limiter);
	waitpid(pid, &va->watatus, 0);
	close(here_pipe[1]);
	if (va->watatus != 0)
		return (-1);
	return (0);
}
