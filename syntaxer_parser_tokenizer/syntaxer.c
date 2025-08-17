/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:49:21 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 00:26:25 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_skip(char *in)
{
	int	i;
	int	type;

	i = 1;
	type = in[0];
	while (in[i] && in[i] != type)
		i++;
	return (i);
}

int	quote_checker(char *in)
{
	int		i;
	int		quote;
	char	type;

	quote = 0;
	i = 0;
	while (in[i])
	{
		if (in[i] == '\'' || in[i] == '\"')
		{
			quote = 1;
			type = in[i];
			i++;
			while (in[i] && in[i] != type)
				i++;
			if (in[i] == type)
				quote = 0;
		}
		if (in[i])
			i++;
	}
	if (quote == 1)
		return (ft_printf(2, "syntax error. unclosed quotes in \"%s\"\n", in));
	return (0);
}

int	line_empty(char *in)
{
	int	i;

	i = 0;
	while (in[i] && ft_isprint(in[i]) == 0)
		i++;
	if (!in[i])
		return (-1);
	return (0);
}

int	piperror(char *in)
{
	int	i;

	i = 0;
	while (in[i] && in[i] == ' ')
		i++;
	if (in[i] && in[i] == '|')
		return (ft_printf(2, "syntax error near unexpected token '|'\n"));
	i = ft_strlen(in) - 1;
	while (in[i] && in[i] == ' ')
		i--;
	if (in[i] && in[i] == '|')
		return (ft_printf(2, "syntax error near unexpected token '|'\n"));
	i = 0;
	while (in[i])
	{
		if (in[i] == '\'' || in[i] == '\"')
			i += quote_skip(&in[i]);
		i++;
		if (in[i] && in[i] == '|' && in[i + 1] == '|')
			return (ft_printf(2, "syntax error near unexpected token '|'\n"));
	}
	return (0);
}

int	syntaxer(char *in)
{
	if (line_empty(in) != 0)
		return (-1);
	if (quote_checker(in) != 0)
		return (-1);
	if (piperror(in) != 0)
		return (-1);
	if (chevron_err(in) != 0)
		return (-1);
	if (chevron_err2(in) != 0)
		return (-1);
	return (0);
}
