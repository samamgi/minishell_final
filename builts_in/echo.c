/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:45:19 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:45:29 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_echo(char **ag, int c)
{
	int	i;

	i = 0;
	while (ag[i])
	{
		printf("%s", ag[i]);
		i++;
		if (ag[i])
			printf(" ");
	}
	if (c == 1)
		printf("\n");
}

static int	flag_skip(char *ag)
{
	int	i;

	i = 1;
	if (ag[0] == '-')
	{
		while (ag[i] && ag[i] == 'n')
			i++;
		if (ag && ag[i])
			return (0);
		return (1);
	}
	return (0);
}

int	ft_echo(t_vars *va, char **args)
{
	int	i;

	i = 1;
	va->watatus = 0;
	while (args[i] && flag_skip(args[i]) == 1)
		i++;
	if (!args[1] || flag_skip(args[1]) == 0)
		put_echo(&args[i], 1);
	else
		put_echo(&args[i], 0);
	return (1);
}
