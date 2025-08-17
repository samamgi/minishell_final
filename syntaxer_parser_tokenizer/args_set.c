/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:22:06 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/13 02:34:26 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*filecpy(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = ft_calloc((ft_strlen(s1), +ft_strlen(s2) + 2), sizeof(char *));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[j] = s1[i];
		j++;
		i++;
	}
	dest[ft_strlen(s1)] = ' ';
	j = ft_strlen(s1) + 1;
	i = 0;
	while (s2[i])
	{
		dest[j] = s2[i];
		i++;
		j++;
	}
	return (dest[j] = 0, dest);
}

void	infilecpy(t_list **node, int *i)
{
	while ((ft_strcmp((*node)->arguments[i[0]], "<") == 0
			|| ft_strcmp((*node)->arguments[i[0]], "<<") == 0)
		&& (*node)->arguments[i[0] + 1])
	{
		(*node)->infile[i[2]] = filecpy((*node)->arguments[i[0]],
				(*node)->arguments[i[0] + 1]);
		i[0] += 2;
		i[2]++;
	}
}

void	outfilecpy(t_list **node, int *i)
{
	while ((ft_strcmp((*node)->arguments[i[0]], ">") == 0
			|| ft_strcmp((*node)->arguments[i[0]], ">>") == 0)
		&& (*node)->arguments[i[0] + 1])
	{
		(*node)->outfile[i[1]] = filecpy((*node)->arguments[i[0]],
				(*node)->arguments[i[0] + 1]);
		i[0] += 2;
		i[1]++;
	}
}
