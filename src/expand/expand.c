/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:28:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/30 19:14:40 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expand.h"
#include "./../libft/libft.h"

#define EXPANDER_ESC_CHS "' "

typedef struct s_command t_command;
typedef struct s_command {
    char        **args;
    int         argc;
};

void *alloc(ssize_t size);

char *trim_expandable(char *str)
{
    int counter;
    int check;
    char *expandable;

    counter = 0;
    while (str[counter] != '$')
        counter++;
    check = counter;
    while (!in(EXPANDER_ESC_CHS, str[counter]) && str[counter])
        counter++;
    expandable = alloc((counter - check + 2) * sizeof(char));
    strncmp(src=str, dest=expandable, start=check, n=counter-check+1);
}
char *expand_str(char *str)
{
    
}

void expand_command(t_command *command)
{
    int counter;

    counter = 0;
    while (counter < command->argc)
    {
        if (in(command->args[counter], '$'))
            expand_str(command->args[counter]);
        counter++;
    }
}