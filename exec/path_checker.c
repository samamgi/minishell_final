/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:42:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:43:04 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_path_util4(t_vars *va, char *str)
{
	if (str && access(str, F_OK) == 0 && access(str, X_OK) != 0)
	{
		va->watatus = 126;
		ft_printf(2, "minishell: permission denied: %s\n", str);
		return (0);
	}
	else if (str && access(str, F_OK) == 0)
		return (1);
	else
	{
		va->watatus = 127;
		ft_printf(2, "minishell: command not found: %s\n", str);
		return (0);
	}
}

static int	check_path_util3(t_list *lst, char **paths)
{
	int		i;
	char	*cmd;
	char	*str;

	i = 1;
	if (lst->com && ft_strcmp(lst->com, "") == 0)
		return (0);
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(str, lst->com);
		ft_free(str);
		if (access(cmd, F_OK) == 0)
		{
			free(lst->com);
			lst->com = ft_strdup(cmd);
			return (free_tab(paths));
		}
		ft_free(cmd);
		i++;
	}
	return (0);
}

static int	check_path_util2(t_vars *va, char *line, char **paths, t_list *lst)
{
	int	i;

	i = 0;
	if (lst->com[0] == '/' && access(lst->com, X_OK) != 0)
	{
		va->watatus = 126;
		ft_printf(2, "minishell: permission denied: %s\n", lst->com);
		return (0);
	}
	while (va->envi[i] && ft_strnstr(va->envi[i], "PATH", 4) == 0)
		i++;
	line = va->envi[i];
	if (line)
		paths = ft_split(line, ':');
	if (!paths)
		return (ft_printf(2, "minishell: command not found: %s\n", lst->com));
	if (check_path_util3(lst, paths) == 1)
		return (1);
	free_tab(paths);
	return (check_path_util4(va, lst->com));
}

int	dir_checker(t_vars *va, char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir != NULL)
	{
		va->watatus = 126;
		closedir(dir);
		ft_printf(2, "minishell: %s: Is a directory.\n", cmd);
		return (0);
	}
	return (1);
}

int	path_checker(t_vars *va, t_list *lst)
{
	char	*line;
	char	**paths;

	line = NULL;
	paths = NULL;
	if (!lst->com)
	{
		va->watatus = 0;
		return (0);
	}
	if (dir_checker(va, lst->com) == 0)
		return (0);
	if (lst->com[0] == '/' && access(lst->com, F_OK) == 0)
		return (1);
	else if (lst->com[0] == '/' && access(lst->com, F_OK) != 0)
	{
		va->watatus = 127;
		ft_printf(2, "minishell: no such file or directory: %s\n", lst->com);
		return (0);
	}
	return (check_path_util2(va, line, paths, lst));
}
