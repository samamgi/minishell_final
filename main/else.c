/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:13:20 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:13:22 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	stop(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**set_env(t_vars *va, char **env)
{
	char	**env_tab;
	char	**tab;
	int		i;
	int		j;

	env_tab = cpy_tab(env);
	tab = ft_calloc (6, sizeof (char *));
	tab[0] = getcwd(tab[0], 0);
	tab[1] = ft_strjoin("HOME=", tab[0]);
	tab[2] = ft_strjoin("PWD=", tab[0]);
	tab[3] = ft_strjoin("OLDPWD=", tab[0]);
	tab[4] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:"
			"/usr/sbin:/usr/bin:/sbin:/bin");
	i = 1;
	while (tab[i] != NULL)
	{
		j = 0;
		while (env_tab[j] && ft_strncmp(tab[i], env_tab[j], stop(tab[i])) != 0)
			j++;
		if (!env_tab[j])
			env_tab = ft_export_1a(va, i, tab, env_tab);
		i++;
	}
	free_tab(tab);
	return (env_tab);
}

char	**cpy_tab(char **tab)
{
	int		i;
	char	**ret;

	i = 0;
	while (tab[i])
		i++;
	ret = ft_calloc(i + 1, sizeof (char **));
	i = 0;
	while (tab[i])
	{
		ret[i] = ft_strdup(tab[i]);
		i++;
	}
	return (ret);
}

int	ft_strcmp(char *src, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (src == NULL || dest == NULL)
		return (-1);
	while (src[i])
	{
		if (src[i] == dest[i])
			i++;
		else
			return (src[i] - dest[i]);
	}
	return (0);
}
