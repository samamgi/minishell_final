/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_maker_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:19:27 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 02:33:16 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	out_checker(t_vars *va, char **out2)
{
	char	*content;
	int		i;

	i = 0;
	while (out2[i])
	{
		content = getfile(out2[i]);
		if (output_access_checker(va, content) != 0)
		{
			free(content);
			return (-1);
		}
		i++;
		free(content);
	}
	return (0);
}

int	in_checker(t_vars *va, char **in2)
{
	char	*content;
	int		i;

	i = 0;
	while (in2[i])
	{
		if (in2[i][1] != '<')
		{
			content = getfile(in2[i]);
			if (input_access_checker(va, content) != 0)
			{
				free(content);
				return (-1);
			}
			free(content);
		}
		i++;
	}
	return (0);
}

int	input_access_checker(t_vars *va, char *content)
{
	if (dir_checker(va, content) == 0)
		return (1);
	if (access(content, F_OK) != 0)
		return (ft_printf(2, "minishell: no such content or directory: %s\n",
				content));
	else if (access(content, R_OK) != 0)
		return (ft_printf(2, "minishell: permission denied: %s\n", content));
	return (0);
}

int	output_access_checker(t_vars *va, char *content)
{
	if (dir_checker(va, content) == 0)
		return (1);
	if (access(content, W_OK) != 0 && access(content, F_OK) == 0)
		return (ft_printf(2, "minishell: permission denied: %s\n", content));
	return (0);
}
