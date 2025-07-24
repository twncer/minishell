/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:21:20 by btuncer           #+#    #+#             */
/*   Updated: 2025/07/18 17:49:24 by root             ###   ########.fr       */
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
#include "./expand/expand.h"

void print_prefix();
t_env *init_env();
void print_env();
int valid_dollar_count(char *str);

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

char **queue_expandables(char *str);
void expand_queue(char **queue);
void implement_queue(char **prompt, char **queue);

int main()			
{
	char *prompt;
	char **queue;
	int counter = 0;
	
	init_env();
	
	write(1, "EXPANDABLE GIR > ", 17);
	print_prefix();
	prompt = readline(PROMPT);
	printf("\nPROMPT: >%s<\n\n\n", prompt);

	queue = queue_expandables(prompt);

	printf("___ EXPANDABLES ___\n\n");
	while (queue[counter])
	{
		printf("> |%s\n", queue[counter]);
		counter++;
	}

	expand_queue(queue);
	counter = 0;
	
	printf("\n___ EXPANDED QUEUE ___\n\n");
	while (queue[counter])
	{
		printf("> |%s\n", queue[counter]);
		counter++;
	}

	printf("\n\n> expander tool:\n");
	printf("OLD_LEN: %d\nNEW_LEN: %d\n", get_expander(0)->old_len, get_expander(0)->new_len);

	printf("\n\n-- FINAL OUTPUT: --\n");
	implement_queue(&prompt, queue);
	printf(">%s<\n", prompt);

	exit(0);
	xshell_signals();
	xshell();
	exit(0);
}

// echo $'burak' => burak
// echo $"burak" => $burak




















