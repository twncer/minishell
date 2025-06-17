/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xshell_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:52:04 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/01 17:33:59 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "./../xshell.h"

ssize_t	len(char *str);
void print_prefix();

static void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(1, "\n", 1);
        print_prefix();
        write(1, PROMPT, len(PROMPT));
    }
}

void xshell_signals()
{
    struct sigaction sigact;
    
    sigact.sa_handler = signal_handler;
    sigact.sa_flags = 0;
    sigemptyset(&sigact.sa_mask);
    
    if (sigaction(SIGINT, &sigact, 0) == -1)
        exit(1);
    sigact.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sigact, 0) == -1)
        exit(1);
}
