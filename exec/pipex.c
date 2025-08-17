/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:46:39 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:46:42 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(t_vars *va)
{
	close(va->pipe1[1]);
	close(va->pipe1[0]);
	close(va->pipe2[1]);
	close(va->pipe2[0]);
}

static int	killshell(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (lst->next)
	{
		if (lst->com && ft_strnstr(lst->com, "minishell\0",
				ft_strlen(lst->com)) != NULL)
			return (1);
		lst = lst->next;
	}
	lst = tmp;
	return (0);
}

int	pipex(t_vars *va, t_list *lst)
{
	int		i;

	if (killshell(lst) == 1)
		return (ft_printf(2, "ERROR. cannot execute './minishell'"
				"inside pipe\n"));
	pipe(va->pipe1);
	pipe(va->pipe2);
	i = 0;
	loop(va, lst);
	return (0);
}
