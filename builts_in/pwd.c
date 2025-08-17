/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:32:01 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:32:04 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_vars *va)
{
	char	*pth;
	char	*pth2;

	pth = NULL;
	pth2 = getcwd(pth, 0);
	if (pth2 == NULL)
		return (printf("minishell: pwd: ERROR. cannot access"
				"current working directory.\n"));
	va->watatus = 0;
	printf("%s\n", pth2);
	free(pth);
	free(pth2);
	return (1);
}
