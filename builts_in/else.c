/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:34:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/08/17 03:34:53 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_ex2(void)
{
	printf("        .  '        +        ,='  \\='/ \\'=/  '=,           *  +\n");
	printf(" *                 *      ,='  ,=='||   ||'==,  '=,\n");
	printf("    +  .  Cut up!     ,=' ,==='    ||. .||    '===, '=,\n");
	printf("                   ,'.==='          \\| |/   *      '===,',\n");
	printf("                 /,='      '        || ||     '         '=,\\\n");
	printf("               '          + .       || ||        .   *       '\n");
	printf("    LYFE is a                       '|'|'     i thiNk we're\n");
	printf("         G r A v e                   \\:/       D O O M E D\n");
	printf("   *  .                      +       \\|/\n");
	printf("                and i dig iT.         |    '\n");
	printf("                                      |\n");
}

int	print_hex(t_vars *va)
{
	int	i;

	i = 0;
	while (i++ != 2)
		printf("\n");
	printf("                                      |\n");
	printf("                     . *        𓆌     |      .    +\n");
	printf("   .                  +              /|\\\n");
	printf(" '      Al0ne                        /:\\  te amo\n");
	printf("           2geTher          15      ,|,|,          *\n");
	printf("               ,                    || ||             .      ,\n");
	printf("                 \\'=,      .   '    || ||     '  .      ,='/\n");
	printf("  CYFM<3           ','===,          /| |\\          ,===','\n");
	printf("                      '=, '===,    ||' '||    ,===' ,='\n");
	printf(" .'      .  ` *           '=,  '==,||   ||,=='  ,='      REPENT!\n");
	printf("               W2DT          '=,  /=,\\ /,=\\  ,='    .    '\n");
	printf("                        one     ><  >=-=<  ><     one\n");
	print_ex2();
	while (i++ != 4)
	{
		printf("\n");
	}
	va->watatus = 8 * 256;
	return (1);
}
