/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:07:01 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:07:02 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_close(int *file)
{
	int	i;

	i = 0;
	while (file && file[i] != 0)
	{
		if (file[i] > 0)
			close(file[i]);
		i++;
	}
	free(file);
}

static void	free_node(t_list *lst)
{
	free_tab(lst->arguments);
	free_tab(lst->outfile);
	free_tab(lst->infile);
	if (lst->next)
		free(lst->next);
	if (lst->com)
		free(lst->com);
}

void	free_lst(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	while (1)
	{
		free_node(lst);
		if (!lst->prev)
			break ;
		lst = lst->prev;
	}
	free(lst);
}
