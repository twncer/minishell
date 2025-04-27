/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:10:38 by btuncer           #+#    #+#             */
/*   Updated: 2025/04/27 01:12:58 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool is_str_empty(char *str)
{
    int counter;
    bool is_empty;
    
    counter = 0;
    is_empty = true;
    while (str[counter] && is_empty)
    {
        if (str[counter] != ' ')
            is_empty = false;
        counter++;
    }
    return (is_empty);
}