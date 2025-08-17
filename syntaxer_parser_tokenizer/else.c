/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:43:45 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/14 00:33:15 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_files(char **tab, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!tab || !c)
		return (0);
	while (tab[i])
	{
		if (!tab[i][0])
			return (0);
		if (tab[i] && tab[i][0] == c)
			j++;
		i++;
	}
	if (j)
		j++;
	return (j);
}

t_list	*node_init(char *cmd)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->arguments = NULL;
	node->arguments = wrdsplit(cmd);
	if (!node->arguments)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->com = NULL;
	node->infile = NULL;
	node->infile = ft_calloc(count_files(node->arguments, '<') + 1,
			sizeof(char *));
	node->fd_in = 0;
	node->outfile = NULL;
	node->outfile = ft_calloc(count_files(node->arguments, '>') + 1,
			sizeof(char *));
	node->fd_out = 0;
	if (!node->infile || !node->outfile)
		return (NULL);
	return (node);
}

void	chevrons(char **in, char **res, int *i, int *j)
{
	if ((*in)[(*i)] && ((*in)[(*i)] == '<' || (*in)[(*i)] == '>'
			|| (*in)[(*i)] == '|'))
	{
		if (((*in)[*i] == '<' && (*in)[(*i) + 1] == '<') || ((*in)[(*i)] == '>'
				&& (*in)[(*i) + 1] == '>'))
		{
			if ((*res)[(*j) && (*res)[(*j)] != ' '])
				(*res)[(*j)++] = ' ';
			(*res)[(*j)++] = (*in)[(*i)++];
			(*res)[(*j)++] = (*in)[(*i)++];
			if ((*in)[(*i)] != ' ')
				(*res)[(*j)++] = ' ';
		}
		else
		{
			if ((*res)[(*j) && (*res)[(*j)] != ' '])
				(*res)[(*j)++] = ' ';
			(*res)[(*j)++] = (*in)[(*i)++];
			if ((*in)[(*i)] != ' ')
				(*res)[(*j)++] = ' ';
		}
	}
	else
		(*res)[(*j)++] = (*in)[(*i)++];
}
