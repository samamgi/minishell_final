/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:31 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:02:46 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_counter(char *in)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (in[i])
	{
		if (in[i] && in[i] == '|')
			count++;
		if (in[i] && (in[i] == '\'' || in[i] == '\"'))
			i += quote_skip(&in[i]);
		i++;
	}
	return (count);
}

char	**cmdsplit(char *in)
{
	char	**res;
	int		i[2];
	int		start;

	i[0] = 0;
	i[1] = 0;
	start = 0;
	res = ft_calloc(pipe_counter(in) + 2, sizeof (char *));
	if (!res)
		return (NULL);
	while (in[i[0]])
	{
		if (in[i[0]] && (in[i[0]] == '\'' || in[i[0]] == '\"'))
			i[0] += quote_skip(&in[i[0]]);
		i[0]++;
		if ((in[i[0]] && in[i[0]] == '|'))
		{
			res[i[1]] = ft_substr(in, start, i[0] - start);
			i[1]++;
			i[0]++;
			start = i[0];
		}
	}
	res[i[1]] = ft_substr(in, start, i[0] - start);
	return (res);
}
