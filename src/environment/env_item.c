/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:28:17 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/16 20:14:23 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"
#include "./../libft/libft.h"
#include <stdio.h>

void *alloc(ssize_t);

t_env_item *new_env_item(char *key, char *val)
{
    t_env_item *new_item;
    
    new_item = alloc(sizeof(t_env_item));
    if (!new_item)
        return (NULL);
    new_item->key = alloc(len(key) * sizeof(char) + 1);
    new_item->value = alloc(len(val) * sizeof(char) + 1);
    if (!new_item->key || !new_item->value)
        return ((void *)0); // free atcan mi?
    ft_strcpy(key, new_item->key);
    ft_strcpy(val, new_item->value);
    new_item->next = (void *)0;
    return (new_item);
}
