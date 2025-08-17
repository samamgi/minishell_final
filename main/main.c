/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:13:12 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:13:15 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	terminal_start(int ac, char **av, char **env)
{
	int		pid;
	char	**ag;

	(void)env;
	(void)av;
	(void)ac;
	ag = ft_calloc(2, sizeof (char *));
	if (!ag)
		return ;
	ag[0] = ft_strdup("clear");
	ag[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/clear", ag, env);
		ft_printf(2, "error\n");
		exit(0);
	}
	wait(0);
	free(ag[0]);
	free(ag);
}

static char	*get_path(void)
{
	char	*str;
	char	*res;

	str = getcwd(NULL, 0);
	if (str == NULL)
		return (NULL);
	res = ft_strjoin(str, "-$ ");
	if (res == NULL)
		return (NULL);
	free(str);
	return (res);
}

void	reset_fd(t_vars *va)
{
	dup2(va->fd[0], STDIN_FILENO);
	dup2(va->fd[1], STDOUT_FILENO);
	dup2(va->fd[2], STDERR_FILENO);
	close (va->fd[2]);
	close (va->fd[1]);
	close (va->fd[0]);
}

static char	*init_reading(t_vars *va)
{
	char	*str;

	va->fd[0] = dup(STDIN_FILENO);
	va->fd[1] = dup(STDOUT_FILENO);
	va->fd[2] = dup(STDERR_FILENO);
	signal(2, &handle);
	signal(SIGQUIT, SIG_IGN);
	va->current_path = get_path();
	str = readline(va->current_path);
	free(va->current_path);
	if (str == NULL)
		file_end(str, va);
	return (str);
}

int	main(int ac, char **av, char **env)
{
	static struct s_vars	va;
	t_list					*lst;
	char					**tab;
	char					*str;

	tab = NULL;
	va.envi = set_env(&va, env);
	terminal_start(ac, av, va.envi);
	while (1)
	{
		str = init_reading(&va);
		lst = NULL;
		new_lst(&va, str, tab, &lst);
		if (lst)
		{
			if (file_opener(&va, lst) != -1)
				exe(&va, lst);
			free_lst(lst);
		}
		reset_fd(&va);
	}
	return (0);
}
