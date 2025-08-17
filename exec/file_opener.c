/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:24:23 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:24:23 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getfile(char *str)
{
	char	*file;

	if (str[1] == '<' || str[1] == '>')
		file = ft_substr(str, 3, ft_strlen(str));
	else
		file = ft_substr(str, 2, ft_strlen(str));
	return (file);
}

int	in_opener(t_vars *va, t_list *lst)
{
	int		i;
	char	*file;

	i = 0;
	while (lst->infile[i])
	{
		file = getfile(lst->infile[i]);
		if (lst->infile[i] && lst->infile[i][1] != '<')
		{
			lst->fd_in = open(file, O_RDONLY);
			free(file);
		}
		else if (heredoc(va, lst, file) == -1)
			return (-1);
		i++;
		if (lst->fd_in == -1)
			return (-1);
		if (lst->infile[i] && lst->fd_in > 1)
			close(lst->fd_in);
	}
	return (0);
}

int	out_opener(t_list *lst)
{
	int		i;
	char	*file;

	i = 0;
	while (lst->outfile[i])
	{
		file = getfile(lst->outfile[i]);
		if (lst->outfile[i] && lst->outfile[i][1] != '>')
			lst->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			lst->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(file);
		i++;
		if (lst->fd_out == -1)
			return (-1);
		if (lst->outfile[i] && lst->fd_out > 1)
			close(lst->fd_out);
	}
	return (0);
}

int	file_opener(t_vars *va, t_list *lst)
{
	int	check;

	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		check = 0;
		if (in_opener(va, lst) == -1)
		{
			if (va->watatus == 256)
			{
				lst_close(lst);
				g_signal = 130;
				return (-1);
			}
			else
				g_signal = 0;
			check = 42;
		}
		if (check == 0)
			out_opener(lst);
		lst = lst->next;
	}
	return (0);
}
