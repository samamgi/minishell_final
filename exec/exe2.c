/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:00:29 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:00:31 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_sw(int in[2], int out[2])
{
	int	tmp;

	tmp = in[1];
	in[1] = out[1];
	out[1] = tmp;
	tmp = in[0];
	in[0] = out[0];
	out[0] = tmp;
	close(in[0]);
	close(in[1]);
	pipe(in);
}

void	onecom(t_vars *va, t_list *lst)
{
	if (dup_maker(va, lst) == 0)
	{
		lst_close(lst);
		if (builts_in(va, lst) == 0)
		{
			va->pid[0] = fork();
			if (va->pid[0] == 0)
			{
				close(va->fd[2]);
				close(va->fd[1]);
				close(va->fd[0]);
				signal(2, NULL);
				signal(3, NULL);
				if (path_checker(va, lst) == 1)
					execve(lst->com, lst->arguments, va->envi);
				free_end(va, lst);
			}
		}
	}
}

static void	loop_util(t_vars *va, t_list *lst)
{
	signal(2, NULL);
	signal(3, NULL);
	lst_close(lst);
	close_fd(va);
	if (builts_in(va, lst) == 0)
		if (path_checker(va, lst) == 1)
			execve(lst->com, lst->arguments, va->envi);
}

void	loop(t_vars *va, t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		va->pid[i] = fork();
		if (va->pid[i] == 0)
		{
			close(va->fd[2]);
			close(va->fd[1]);
			close(va->fd[0]);
			if (dup_maker(va, lst) == 0)
				loop_util(va, lst);
			else
				lst_close(lst);
			close_fd(va);
			free_end(va, lst);
		}
		pipe_sw(va->pipe2, va->pipe1);
		lst = lst->next;
		i++;
	}
}
