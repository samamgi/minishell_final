/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:55:29 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 01:55:30 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_findstr(const char *str, const char *src, int len)
{
	int	i;
	int	j;

	i = -1;
	while ((i != len && str[i] != '\0') || i == -1)
	{
		j = 0;
		while (str[i++] == src[j++])
			if (src[j] == '\0')
				return (1);
	}
	return (0);
}

int	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (1);
}

int	tab_len(char **tab)
{
	int	i;

	i = 1;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	lst_count(t_list *lst)
{
	int	i;

	i = 1;
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
