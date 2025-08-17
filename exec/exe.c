/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:53:25 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:53:27 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_code(int code)
{
	if (code == 0)
		return (0);
	else if (code >= 256)
		return (code / 256);
	else
		return (code + 128);
}

void	wait_exe(t_vars *va)
{
	int	i;

	i = 0;
	while (va->pid[i])
	{
		waitpid(va->pid[i], &va->watatus, 0);
		if (va->watatus == 139)
		{
			va->watatus = va->watatus * 256;
			ft_printf(2, "Segmentation fault (core dumpted)\n");
		}
		else if (va->watatus == 15)
			ft_printf(2, "Terminated\n");
		else if (va->watatus == 131)
		{
			va->watatus = va->watatus * 256;
			ft_printf(2, "Quit (core dumpted)\n");
		}
		i++;
	}
	free(va->pid);
}

void	exe(t_vars *va, t_list *lst)
{
	va->pid = ft_calloc(lst_count(lst) + 1, sizeof(int));
	if (!va->pid)
		return ;
	g_signal = -2;
	while (lst->prev)
		lst = lst->prev;
	if (lst_count(lst) == 1)
		onecom(va, lst);
	else
	{
		pipex(va, lst);
		lst_close(lst);
	}
	wait_exe(va);
	close_fd(va);
	g_signal = get_code(va->watatus);
	va->last_code = g_signal;
}
