/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:26:03 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:26:04 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	annex(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) != 0 || str[i] == '$')
	{
		i++;
		if (str[i] == '?')
			i++;
	}
	return (i);
}

static char	*var_env_inquote(t_vars *va, char *in,
		char *res, int *i)
{
	char	*env_va;
	char	*tmp;

	tmp = ft_substr(&in[i[0]], 0, annex(&in[i[0]]));
	if (!tmp)
		return (NULL);
	env_va = getvar(va, tmp);
	if (!env_va)
		return (NULL);
	i[0] += ft_strlen(tmp);
	i[1] += ft_strlen(env_va);
	free(tmp);
	if (res && env_va)
		tmp = ft_strjoin(res, env_va);
	if (!tmp)
		return (NULL);
	free(res);
	res = ft_calloc(ft_strlen(in) + ft_strlen(env_va) + 1,
			sizeof (char *));
	if (!res)
		return (NULL);
	ft_strlcpy(res, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	free(env_va);
	return (res);
}

static char	*double_quote(t_vars *va, char *in, char *res, int *i)
{
	i[0]++;
	while (in[i[0]] && in[i[0]] != 34)
	{
		if (in[i[0]] == '$')
			res = var_env_inquote(va, in, res, i);
		else if (in[i[0]] == 34)
			i[0]++;
		else if (res && in)
		{
			res[i[1]] = in[i[0]];
			i[0]++;
			i[1]++;
		}
	}
	i[0]++;
	return (res);
}

static void	single_quote(char *in, char *res, int *i)
{
	i[0]++;
	while (in[i[0]] && in[i[0]] != 39)
	{
		res[i[1]] = in[i[0]];
		i[0]++;
		i[1]++;
	}
	i[0]++;
}

char	*killquote(t_vars *va, char *str)
{
	int		i[2];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (str[i[0]])
	{
		if (str[i[0]] == '$')
			res = var_env_inquote(va, str, res, i);
		else if (str[i[0]] == '\"')
			res = double_quote(va, str, res, i);
		else if (str[i[0]] == '\'')
			single_quote(str, res, i);
		else if (res && str)
		{
			res[i[1]] = str[i[0]];
			i[0]++;
			i[1]++;
		}
	}
	return (res);
}
