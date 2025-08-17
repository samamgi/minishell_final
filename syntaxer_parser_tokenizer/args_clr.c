/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_clr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:02:30 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/13 02:29:20 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_clr(t_vars *va, char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = killquote(va, str);
	free(str);
	if (!res)
		return (NULL);
	return (res);
}

void	file_clr(t_vars *va, t_list **node)
{
	int	i;

	i = 0;
	while ((*node)->arguments[i])
	{
		(*node)->arguments[i] = str_clr(va, (*node)->arguments[i]);
		i++;
	}
	i = 0;
	while ((*node)->infile[i])
	{
		(*node)->infile[i] = str_clr(va, (*node)->infile[i]);
		i++;
	}
	i = 0;
	while ((*node)->outfile[i])
	{
		(*node)->outfile[i] = str_clr(va, (*node)->outfile[i]);
		i++;
	}
	(*node)->com = str_clr(va, (*node)->com);
}

static int	arg_clr_count(t_list *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->arguments[i])
	{
		if (node->arguments[i][0] == '<' || node->arguments[i][0] == '>')
			i = i + 2;
		else
		{
			i++;
			j++;
		}
	}
	return (j + 1);
}

void	arg_clr(t_list **node)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = ft_calloc(arg_clr_count(*node) + 1, sizeof(char *));
	if (!tab)
		return ;
	while ((*node)->arguments[i])
	{
		if ((*node)->arguments[i][0] == '<' || (*node)->arguments[i][0] == '>')
			i = i + 2;
		else
		{
			tab[j] = ft_strdup((*node)->arguments[i]);
			if (!tab[j] || !(*node)->arguments[i])
				break ;
			i++;
			j++;
		}
	}
	free_tab((*node)->arguments);
	(*node)->arguments = tab;
}
