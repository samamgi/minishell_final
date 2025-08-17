/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:17:36 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:17:37 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	tab_sw(char **s1, char **s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup((*s1));
	tmp2 = ft_strdup((*s2));
	free((*s1));
	free((*s2));
	(*s1) = ft_strdup(tmp2);
	(*s2) = ft_strdup(tmp1);
	free(tmp1);
	free(tmp2);
}

static int	is_sorted(char **tab)
{
	int	i;

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_print(char **tab)
{
	int		i;
	int		j;
	char	*s1;
	char	*s2;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] != '=')
			j++;
		j++;
		s1 = ft_substr(tab[i], 0, j);
		s2 = ft_substr(tab[i], j, ft_strlen(tab[i]));
		printf("export %s\"%s\"\n", s1, s2);
		i++;
		free (s1);
		free (s2);
	}
}

char	**ft_print_export(t_vars *va, char **env)
{
	char	**print;

	print = cpy_tab(env);
	while (is_sorted(print) != -1)
		tab_sw(&print[is_sorted(print)],
			&print[is_sorted(print) + 1]);
	ft_print(print);
	free_tab(print);
	va->watatus = 0;
	return (env);
}

char	**export_util1(t_vars *va, char **args, char **env)
{
	int		i;
	char	**res;

	i = 1;
	va->watatus = 0;
	res = cpy_tab(env);
	free_tab(env);
	if (!args[1])
		return (ft_print_export(va, res));
	while (args[i])
	{
		res = ft_export_1a(va, i, args, res);
		i++;
	}
	return (res);
}
