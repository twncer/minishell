/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:21:20 by btuncer           #+#    #+#             */
/*   Updated: 2025/04/27 01:58:50 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libms/libms.h"
#include "./signals/xshell_signals.h"

// __attribute__((destructor))
// void cya()
// {
// }

void xshell()
{
    char *prompt;

    using_history();
    while (1)
    {
        prompt = readline("xshell$ ");
        add_history(prompt);
        free(prompt);
    }
}

int main()
{
    xshell_signals();
    xshell();
    exit(0);
}
