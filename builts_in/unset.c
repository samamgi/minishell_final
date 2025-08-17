/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:32:38 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:32:42 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	var_finder(char *var, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i] && env[i][j] != '=')
			j++;
		tmp = ft_substr(env[i], 0, j);
		if (ft_strncmp(var, tmp, ft_strlen(var)) == 0)
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (-1);
}

static char	**unset_tool(char *var, char **env)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = ft_calloc(tab_len(env) + 1, sizeof(char **));
	while (j <= tab_len(env))
	{
		if (var_finder(var, env) == j)
			j++;
		if (env[j])
			res[i] = ft_strdup(env[j]);
		i++;
		j++;
	}
	return (res);
}

char	**ft_unset(char **ag, char **env)
{
	int		i;
	char	**res;
	char	**cpy;

	i = 1;
	cpy = cpy_tab(env);
	free_tab(env);
	if (!ag[i])
		return (cpy);
	while (ag[i])
	{
		res = unset_tool(ag[i], cpy);
		i++;
		if (ag[i])
		{
			free_tab(cpy);
			cpy = cpy_tab(res);
			free_tab(res);
		}
	}
	free_tab(cpy);
	return (res);
}
