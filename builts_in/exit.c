/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:30:51 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:30:55 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_vars *va, t_list *lst)
{
	if (lst->arguments[2])
		return (ft_printf(2, "minishell: exit: too many arguments\n"));
	else if (lst->arguments[1] && is_num(lst->arguments[1]) == 0)
		ft_printf(2, "minishell: exit: %s: numeric argument requiered\n",
			lst->arguments[1]);
	if (lst->arguments[1] && is_num(lst->arguments[1]) == 1)
		va->watatus = ft_atoi(lst->arguments[1]);
	else if (!lst->arguments[1])
		va->watatus = va->last_code;
	close (va->fd[0]);
	close (va->fd[1]);
	close (va->fd[2]);
	free_end(va, lst);
	return (-1);
}
