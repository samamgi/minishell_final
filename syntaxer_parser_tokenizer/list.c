/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:37:24 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:10:40 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	norm1(t_vars *va, t_list *node, int i, int j)
{
	arg_clr(&node);
	file_clr(va, &node);
	node->infile[i] = NULL;
	node->outfile[j] = NULL;
}

t_list	*add_node(t_vars *va, char *cmd)
{
	t_list	*node;
	int		i[3];

	node = node_init(cmd);
	if (!node)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (node->arguments[i[0]])
	{
		if (node->arguments[i[0]] && (ft_strcmp(node->arguments[i[0]], "<")
				== 0 || ft_strcmp(node->arguments[i[0]], "<<") == 0))
			infilecpy(&node, i);
		else if (node->arguments[i[0]] && (ft_strcmp(node->arguments[i[0]], ">")
				== 0 || ft_strcmp(node->arguments[i[0]], ">>") == 0))
			outfilecpy(&node, i);
		else if (node->com == NULL && node->arguments[i[0]])
			node->com = ft_strdup(node->arguments[i[0]]);
		else
			i[0]++;
	}
	norm1(va, node, i[2], i[1]);
	return (node);
}

static int	norm2(char ***supersplit, char *in, int *i)
{
	if (!(*in))
		return (0);
	add_history(in);
	if (syntaxer(in) == -1)
	{
		free(in);
		return (0);
	}
	(*i) = 0;
	(*supersplit) = cmdsplit(in);
	if (!(*supersplit))
		return (0);
	return (1);
}

static void	norm3(char **supersplit, char *in)
{
	free_tab(supersplit);
	free(in);
}

void	new_lst(t_vars *va, char *in, char **supersplit, t_list **curr)
{
	t_list	*node;
	int		i;

	node = NULL;
	if (norm2(&supersplit, in, &i) == 1)
	{
		while (supersplit[i])
		{
			node = add_node(va, supersplit[i]);
			if (!node)
				break ;
			if (i == 0)
				(*curr) = node;
			else
			{
				(*curr)->next = node;
				node->prev = (*curr);
			}
			(*curr) = node;
			i++;
		}
		norm3(supersplit, in);
	}
}
