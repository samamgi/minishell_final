/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:19:00 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 00:30:22 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	syntax_check2(char *in, int type, int (*i))
{
	if (in[(*i) + 2] && in[(*i) + 2] == type)
		return (ft_printf(2, "syntax error near unexpected token '%c'\n",
				type));
	while (in[(*i)] && in[(*i)] == type)
		(*i)++;
	if (in[(*i)] && (in[(*i)] == '<' || in[(*i)] == '>'))
		return (ft_printf(2, "syntax error near unexpected token '%c'\n",
				in[(*i)]));
	return (0);
}

int	chevron_err2(char *in)
{
	int	i;
	int	type;

	i = 0;
	while (in[i] == ' ')
		i++;
	while (in[i])
	{
		if (in[i] == '>' || in[i] == '<')
		{
			type = in[i];
			if (syntax_check2(in, type, &i) != 0)
				return (42);
		}
		if (in[i] == '\'' || in[i] == '\"')
			i += quote_skip(&in[i]);
		if (in[i])
		i++;
	}
	return (0);
}

static int	syntax_check(char *in, int type, int (*i))
{
	while (in[(*i)] && in[(*i)] == type)
		(*i)++;
	while (in[(*i)] && in[(*i)] == ' ')
		(*i)++;
	if (!in[(*i)])
		return (ft_printf(2, "syntax error near 'newline'\n"));
	if (in[(*i)] == '|' || in[(*i)] == '<' || in[(*i)] == '>')
		return (ft_printf(2, "syntax error near unexpected token '%c'\n",
				in[(*i)]));
	return (0);
}

int	chevron_err(char *in)
{
	int	i;
	int	type;

	i = 0;
	while (in[i])
	{
		if (in[i] == '<' || in[i] == '>')
		{
			type = in[i];
			if (syntax_check(in, type, &i) != 0)
				return (42);
			while (in[i] && in[i] != ' ' && in[i] != '|')
			{
				if (in[i] == '\'' || in[i] == '\"')
					i += quote_skip(&in[i]);
				i++;
			}
		}
		if (in[i])
			i++;
	}
	return (0);
}
