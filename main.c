/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:14:34 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/19 01:09:52 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

void 	test(char *test, char *str, int nb)
{
	int		ret[2];

	if (str)
	{
		ret[0] = printf(   test, str);
		ret[1] = ft_printf(test, str);
	}
	else if (nb)
	{
		ret[0] = printf(   test, nb);
		ret[1] = ft_printf(test, nb);
	}
	else if (nb && str)
	{
		ret[0] = printf(   test, nb, str);
		ret[1] = ft_printf(test, nb, str);
	}
	else
	{
		ret[0] = printf(   test);
		ret[1] = ft_printf(test);
	}
	if (ret[0] == ret[1])
		ft_printf(   "\033[0;32m=> return : %d ✓\033[0m\n", ret[0]);
	else
		ft_printf(   "\033[0;31m=> YOU SHOULD HAVE RETURN %d INSTEAD OF %d !\033[0m\n", ret[0], ret[1]);
	ft_printf("\n");
}

int		main(void)
{
	char 	str[] = "slt ma biche";

	printf("\033[2J\n");
	ft_printf("\n\033[0;33m**********************\n");
	ft_printf("********  %%s  ********\n");
	ft_printf("**********************\033[0m\n\n");
	test("=> %%s : [%s]\n", str, NULL);
	test("=> %%s : [%.15s]\n", str, NULL);
	test("=> %%s : [%.5s]\n", str, NULL);
	test("=> %%s : [%.5 5 .s]\n", str, NULL);
	test("=> %%s : [%.15 -27s]\n", str, NULL);
	test("=> %%s : [%.2 -27s]\n", str, NULL);
	test("=> %%s : [%20s]\n", str, NULL);
	//test("=> %%s : [%*s]\n", str, 5);

	ft_printf("Appuyer sur une touche pour continuer.");
	getchar();

	printf("\033[2J\n");
	ft_printf("\n\033[0;33m**********************\n");
	ft_printf("********  %%d  ********\n");
	ft_printf("**********************\033\n\n");
	test("\033[0;36m=> %%d : [%d]\033[0m\n", NULL, 42);
	test("=> %%d : [%.015d]\n", NULL, 42);
	test("=> %%d : [%.015-027d]\n", NULL, 42);
	test("=> %%d : [%20d]\n", NULL, INT_MAX);
	test("=> %%d : [%20d]\n", NULL, INT_MIN);

	ft_printf("Appuyer sur une touche pour continuer.");
	getchar();
	printf("\033[2J\n");
	ft_printf("\n\033[0;33m**********************\n");
	ft_printf("********  %%p  ********\n");
	ft_printf("**********************\033\n\n");
	test("\033[0;36m=> %%p : [%p]\033[0m\n", str, NULL);
	test("=> %%p : [%.015p]\n", str, NULL);
	test("=> %%p : [%020p]\n", str, NULL);
	test("=> %%p : [%-20p]\n", str, NULL);
	test("=> %%p : [%10p]\n", str, NULL);
	test("=> %%p : [%40.2p]\n", str, NULL);
	test("=> %%p : [%.20-40p]\n", str, NULL);
	test("=> %%p : [%.42-0000042p]\n", str, NULL);

	ft_printf("Appuyer sur une touche pour continuer.");
	getchar();
	printf("\033[2J\n");
	ft_printf("\033[0;33m*********************\n");
	ft_printf("********  %%  ********\n");
	ft_printf("*********************\033[0m\n\n");
	test("=> %% : {%%}\n", NULL, NULL);
	test("=> %% : {%.020%}\n", NULL, NULL);
	test("=> %% : {%40%}\n", NULL, NULL);
	test("=> %% : {%.0. 040%}\n", NULL, NULL);
	test("=> %% : {%%%s%%}\n", str, NULL);


	return (0);
}
