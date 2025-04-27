/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xshell_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:52:04 by btuncer           #+#    #+#             */
/*   Updated: 2025/04/27 01:59:28 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        return ((void)write(1, "xshell$ ", 9));
    else if (signal == SIGQUIT)
    {
        write(1, "exit\n", 5);
        exit(0);
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
    if (sigaction(SIGQUIT, &sigact, 0) == -1)
        exit(1);
}