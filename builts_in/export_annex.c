/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_annex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:21:22 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:21:24 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**export_util3(char *va, char *ag, char **env)
{
	char	**res;
	int		i;

	i = 0;
	while (env[i])
		i++;
	res = ft_calloc(i + 2, sizeof (char **));
	i = 0;
	while (env[i])
	{
		res[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(env);
	res[i] = ft_strjoin(va, ag);
	res[i + 1] = NULL;
	return (res);
}

char	**export_util2(char *va, char *ag, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], va, ft_strlen(va)) == NULL)
		i++;
	if (env[i] == NULL)
		return (export_util3(va, ag, env));
	free(env[i]);
	env[i] = ft_strjoin(va, ag);
	return (env);
}

static int	is_alpha(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && ft_isalnum(str[i]) != 0) || str[i] == '_')
		i++;
	if (str[i] != 0)
		return (0);
	return (1);
}

static int	is_str_else(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_export_1a(t_vars *va, int i, char **ags, char **res)
{
	char	*var;
	char	*ag;
	int		j;

	j = 0;
	while (ags[i][j] && ags[i][j] != '=')
		j++;
	var = ft_substr(ags[i], 0, j);
	ag = ft_substr(ags[i], j, ft_strlen(ags[i]));
	if (is_alpha(var) == 1 && ft_isdigit(ags[i][0]) == 0
		&& is_str_else(ags[i], '=') == 1)
		res = export_util2(var, ag, res);
	else if ((is_alpha(var) != 1 || ft_isdigit(ags[i][0]) != 1)
		&& is_str_else(ags[i], '=') == 1)
	{
		va->watatus = 256;
		ft_printf(2, "minishell: export: %s: not a valid identifier\n",
			ags[i]);
	}
	free(var);
	free(ag);
	return (res);
}
