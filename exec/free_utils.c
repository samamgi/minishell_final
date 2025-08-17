/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:04:46 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:04:47 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	return (1);
}

int	ft_free(void *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
	return (1);
}

void	free_end(t_vars *va, t_list *lst)
{
	free_lst(lst);
	free(va->pid);
	free_tab(va->envi);
	rl_clear_history();
	exit(va->watatus);
}

void	lst_close(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = lst;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if ((*lst->infile) && lst->infile[0] && lst->fd_in > 0)
			close(lst->fd_in);
		if ((*lst->outfile) && lst->outfile[0] && lst->fd_out > 0)
			close(lst->fd_out);
		lst = lst->next;
	}
	lst = tmp;
}
