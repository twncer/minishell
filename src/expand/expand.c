/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:28:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/07/01 17:59:38 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expand.h"
#include "./../libft/libft.h"

#include <stdio.h> // debug

typedef struct s_command t_command;
struct s_command
{
    char        **args;
    int         argc;
};

void *alloc(ssize_t size);

bool is_expander_esc_char(char ch)
{
    return (in(" '$", ch));
}

char *trim_expandable(char *str)
{
    int counter;
    int check;
    char *expandable = alloc(200);

    counter = 0;
    while (str[counter] != '$')
        counter++;
    check = ++counter;
    while (str[counter] && !is_expander_esc_char(str[counter]))
        counter++;
    int gap = counter - check;
    ft_strncpy(str + check, expandable, gap);
    printf("check: %d | counter: %d | gap: %d |\nexpandable: %s\n", check, counter, gap, expandable);
    return NULL;
}
