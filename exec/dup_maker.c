/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:17:22 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:17:23 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	out_util(t_vars *va, t_list *lst)
{
	int	i;

	i = 0;
	if (lst->outfile[0] == NULL && lst->next != NULL)
	{
		dup2(va->pipe2[1], 1);
		close(va->pipe2[0]);
	}
	if (out_checker(va, lst->outfile) != 0)
		return (-1);
	if (lst->outfile[0] != NULL && lst->fd_out > 0)
		dup2(lst->fd_out, 1);
	return (0);
}

int	in_util(t_vars *va, t_list *lst)
{
	int	i;

	i = 0;
	if (lst->infile[0] == NULL && lst->prev != NULL)
	{
		dup2(va->pipe1[0], 0);
		close(va->pipe1[1]);
	}
	if (in_checker(va, lst->infile) != 0)
		return (-1);
	if (lst->infile[0] != NULL && lst->fd_in > 0)
		dup2(lst->fd_in, 0);
	return (0);
}

int	dup_maker(t_vars *va, t_list *lst)
{
	va->watatus = -1;
	if (in_util(va, lst) != 0)
	{
		if (va->watatus == 126)
			va->watatus = 126 * 257;
		else
			va->watatus = 257;
		if (lst->infile[0] && lst->fd_in > 0)
			close(lst->fd_in);
		return (1);
	}
	if (out_util(va, lst) != 0)
	{
		if (va->watatus == 126)
			va->watatus = 126 * 257;
		else
			va->watatus = 257;
		if (lst->outfile[0] && lst->fd_out > 0)
			close(lst->fd_out);
		return (1);
	}
	return (0);
}
