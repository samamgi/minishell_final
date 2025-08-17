/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrdsplit2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:17:21 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:17:22 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quoteskiping(char *quote, char **in2, int *i)
{
	(*quote) = (*in2)[(*i)];
	(*i)++;
	while ((*in2)[(*i)] != (*quote))
		(*i)++;
}

int	wrd_split_count(char *in)
{
	int		i;
	int		j;
	char	quote;
	char	*in2;

	j = 0;
	i = 0;
	in2 = chevronspacer(in);
	if (!in2)
		return (0);
	while (in2[i])
	{
		while (in2[i] && in2[i] != ' ')
		{
			if (in2[i] == '\'' || in2[i] == '\"')
				quoteskiping(&quote, &in2, &i);
			i++;
		}
		while (in2[i] == ' ')
			i++;
		j++;
	}
	return (free(in2), j + 1);
}

char	*wrdmalloc(char const *str, int start, int end)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc((end - start + 1), sizeof(char *));
	if (res == NULL || !str[0])
		return (NULL);
	while (start < end)
	{
		res[i] = str[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
