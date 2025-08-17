/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:58:17 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 00:58:34 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cpyquote(char *in, char *res, int *i, int *j)
{
	int	quote;

	quote = in[(*i)];
	res[(*j)] = in[(*i)];
	(*i)++;
	(*j)++;
	while (in[(*i)] && in[(*i)] != quote)
	{
		res[(*j)] = in[(*i)];
		(*i)++;
		(*j)++;
	}
	if (in[(*i)] == quote)
	{
		res[(*j)] = in[(*i)];
		(*i)++;
		(*j)++;
	}
}

char	*chevronspacer(char *in)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(strlen(in) * 3 + 1, sizeof (char *));
	if (!res)
		return (NULL);
	while (in[i])
	{
		if (in[i] == '\"' || in[i] == '\'')
			cpyquote(in, res, &i, &j);
		else
			chevrons(&in, &res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}
