/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:14:36 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:14:37 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	builts_util(t_vars *va, t_list *lst)
{
	if (lst->com && ft_strncmp(lst->com, "echo\0",
			ft_strlen("echo\0") + 1) == 0)
		return (ft_echo(va, lst->arguments));
	else if (lst->com && ft_strncmp(lst->com, "export\0",
			ft_strlen("export\0") + 1) == 0)
	{
		va->envi = export_util1(va, lst->arguments, va->envi);
		return (1);
	}
	else if (lst->com && ft_strncmp(lst->com, "unset\0",
			ft_strlen("unset\0") + 1) == 0)
	{
		va->envi = ft_unset(lst->arguments, va->envi);
		return (1);
	}
	return (0);
}

int	builts_in(t_vars *va, t_list *lst)
{
	if (lst->com && ft_strncmp(lst->com, "exit\0",
			ft_strlen("exit\0") + 1) == 0)
		return (ft_exit(va, lst));
	else if (lst->com && ft_strncmp(lst->com, "pwd\0",
			ft_strlen("pwd\0") + 1) == 0)
		return (ft_pwd(va));
	else if (lst->com && ft_strncmp(lst->com, "env\0",
			ft_strlen("env\0") + 1) == 0)
		return (print_tab(va->envi));
	else if (lst->com && ft_strncmp(lst->com, "cd\0",
			ft_strlen("cd\0") + 1) == 0)
	{
		if (ft_cd(va, lst->arguments) != 1)
			va->watatus = 257;
		return (1);
	}
	else if (lst->com && ft_strncmp(lst->com, "hex\0",
			ft_strlen("hex\0") + 1) == 0)
		return (print_hex(va));
	return (builts_util(va, lst));
}

