/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrdsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:13:09 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:13:11 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	spliting2(char **in2, int *i, int *start)
{
	int		quote;
	char	type;

	(*start) = (*i);
	quote = 0;
	type = 0;
	while ((*in2)[(*i)] && (quote || (*in2)[(*i)] != ' '))
	{
		if (((*in2)[(*i)] == '\'' || (*in2)[(*i)] == '"')
				&& !quote)
		{
			quote = 1;
			type = (*in2)[(*i)];
		}
		else if (quote && (*in2)[(*i)] == type)
		{
			quote = 0;
			type = 0;
		}
		(*i)++;
	}
}

void	spliting(char ***split, char **in2)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	i = 0;
	j = 0;
	while ((*in2)[i])
	{
		while ((*in2)[i] == ' ')
			i++;
		if (!(*in2)[i])
			break ;
		spliting2(in2, &i, &start);
		(*split)[j] = wrdmalloc((*in2), start, i);
		if (!(*split)[j])
		{
			free_tab((*split));
			(*split) = NULL;
			return ;
		}
		j++;
	}
	(*split)[j] = NULL;
}

char	**wrdsplit(char *in)
{
	char	**split;
	char	*in2;

	in2 = chevronspacer(in);
	if (!in2)
		return (NULL);
	split = ft_calloc(wrd_split_count(in2) + 1, sizeof(char *));
	if (!split)
		return (free(in2), NULL);
	spliting(&split, &in2);
	free(in2);
	return (split);
}
