/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:28:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/27 16:42:30 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expand.h"

void expand_str(char *str)
{
    t_env *env;
    char *ptr;

    ptr = str;
    env = get_env();
    while (*str)
    {
        if (*str == '$') {
            printf("aha\n"); *str = '%'; }
        str++;
    }
}