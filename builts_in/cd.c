/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:28:26 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:28:27 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	oldpwd(t_vars *va)
{
	int		i;
	char	*old;

	i = 0;
	while (va->envi[i] && ft_strncmp(va->envi[i], "OLDPWD=", 7) != 0)
		i++;
	free(va->envi[i]);
	old = getcwd(NULL, 0);
	if (old == NULL)
		old = ft_strdup("");
	va->envi[i] = ft_strjoin("OLDPWD=", old);
	free(old);
	return (1);
}

static int	gethome(t_vars *va)
{
	int		i;
	char	*home;

	i = 0;
	va->watatus = 0;
	while (va->envi[i] && ft_strncmp(va->envi[i], "HOME=", 5) != 0)
		i++;
	home = ft_strdup(va->envi[i]);
	chdir(&home[5]);
	i = 0;
	while (va->envi[i] && ft_strncmp(va->envi[i], "PWD=", 4) != 0)
		i++;
	free(va->envi[i]);
	va->envi[i] = ft_strjoin("PWD=", &home[5]);
	free(home);
	return (1);
}

static void	setpwd(char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		tmp = ft_strdup("");
	while (env[i] && ft_strnstr(env[i], "PWD=", 4) == NULL)
		i++;
	free(env[i]);
	env[i] = ft_strjoin("PWD=", tmp);
	free(tmp);
}

int	ft_cd(t_vars *va, char **args)
{
	oldpwd(va);
	if (args[2])
		return (ft_printf(2, "minishell: cd: too many args.\n"));
	if (!args[1])
		return (gethome(va));
	if (access(args[1], X_OK) != 0 && access(args[1], F_OK) == 0)
		return (ft_printf(2, "minishell: cd: %s: permission denied.\n",
				args[1]));
	if (chdir(args[1]) == -1)
		return (ft_printf(2, "minishell: cd: %s: no such file or directory.\n",
				args[1]));
	va->watatus = 0;
	setpwd(va->envi);
	return (1);
}
