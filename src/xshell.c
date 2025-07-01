/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:21:20 by btuncer           #+#    #+#             */
/*   Updated: 2025/07/01 17:55:46 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "./libft/libft.h"
#include "./signals/xshell_signals.h"
#include "./xshell.h"
#include "./environment/env.h"

void print_prefix();
t_env *init_env();
void print_env();

void e()
{
	print_env();
}

void q()
{
	exit(0);
}

void xshell()
{
	char *prompt;
		
	using_history();
	while (1)
	{
		print_prefix();
		prompt = readline(PROMPT);
		if (prompt == (void *)0)
		{
			free(prompt);
			exit(0); // hm
		}
		if (prompt[0])
		{
			add_history(prompt);
			if (prompt[0] == 'e') e();
			else if (prompt[0] == 'q') q();
			// minishell(prompt);
		}
		free(prompt);
	}
}

__attribute__((destructor))
void cya()
{
	trash_bin(true, NULL);
	printf("exit\n");
}

char *trim_expandable(char *str);

int main()			
{
	char *q = trim_expandable("buraktuncer$selam");
	exit(0);
	init_env();
	xshell_signals();
	xshell();
	exit(0);
}
