/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:21:20 by btuncer           #+#    #+#             */
/*   Updated: 2025/04/30 19:27:21 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "./libms/libms.h"
#include "./signals/xshell_signals.h"
#include "./xshell.h"
#include <unistd.h>

t_trash *create_trash()
{
    t_trash *new_trash;
    
    new_trash = malloc(sizeof(t_trash));
    new_trash->mem = NULL;
    new_trash->next = NULL;
    
    return (new_trash);
}

void trash_bin(bool dump, t_trash *trash)
{
    static t_trash *first_trash = NULL;
    static t_trash *current_trash = NULL;
    t_trash *swap;
    
    if (dump && first_trash)
    {
        current_trash = first_trash;
        while (current_trash)
        {
            if (current_trash->mem)
            free(current_trash->mem);
            swap = current_trash->next;
            free(current_trash);
            current_trash = swap;
        }
        return ;
    }
    if (first_trash == NULL)
    {
        first_trash = trash;
        current_trash = first_trash;
        return ;
    }
    current_trash->next = trash;
    current_trash = current_trash->next;
}

void *alloc(ssize_t size)
{
    void *mem;
    t_trash *new_trash;
    
    mem = malloc(size);
    if (!mem)
    return (NULL);
    new_trash = create_trash();
    new_trash->mem = mem;
    new_trash->next = NULL;
    trash_bin(false, new_trash);
    
    return (mem);
}

void xshell()
{
    char *prompt;
    
    using_history();
    while (1)
    {
        prompt = readline("xshell$ ");
        if (prompt == (void *)0)
        {
            free(prompt);
            exit(0);
        }
        if (prompt[0])
        {
            add_history(prompt);
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

int main()
{
    void *hsi = alloc(2000);
    void *sdf = alloc(2000);
    void *sqf = alloc(2000);
    void *swf = alloc(1000);
    exit(0);
    xshell_signals();
    xshell();
    exit(0);
}
