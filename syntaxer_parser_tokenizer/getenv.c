/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:30:56 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 00:39:55 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	still_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]) != 0)
		i++;
	return (i);
}

static char	*ft_getline(char **env, char *var)
{
	int		i;
	int		j;
	char	*tmp;
	char	*res;

	i = 0;
	j = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	free(var);
	while (env[i] && ft_strncmp(env[i], tmp, ft_strlen(tmp)) != 0)
		i++;
	free(tmp);
	if (!env[i])
		return (ft_strdup(""));
	while (env[i][j] && env[i][j] != '=')
		j++;
	res = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	if (!res)
		return (NULL);
	return (res);
}

static char	*getvar2(t_vars *va, char *var)
{
	char	*tmp;
	char	*tmp2;
	char	*res;

	if (!var)
		return (NULL);
	if (var && var[0] == '?')
		return (ft_itoa(g_signal));
	tmp2 = ft_substr(var, 0, still_alphanum(var));
	if (!tmp2)
		return (NULL);
	tmp = ft_getline(va->envi, tmp2);
	tmp2 = ft_substr(var, still_alphanum(var), ft_strlen(var));
	if (!tmp || !tmp2)
		return (NULL);
	res = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (res);
}

char	*getvar(t_vars *va, char *var)
{
	char	**tab;
	char	*res;
	char	*tmp;
	char	*cpy;
	int		i;

	i = 0;
	res = ft_strdup("");
	tab = ft_split(var, '$');
	if (!res || !tab)
		return (NULL);
	while (tab[i])
	{
		tmp = getvar2(va, tab[i]);
		cpy = ft_strdup(res);
		free(res);
		if (!tmp || !cpy)
			return (NULL);
		res = ft_strjoin(cpy, tmp);
		free(cpy);
		free(tmp);
		i++;
	}
	free_tab(tab);
	return (res);
}
