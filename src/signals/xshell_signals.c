/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xshell_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:52:04 by btuncer           #+#    #+#             */
/*   Updated: 2025/04/29 12:11:40 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        printf("\nxshell$ ");
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
