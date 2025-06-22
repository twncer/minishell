/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:28:17 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/20 18:56:55 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"

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
        return (NULL); // free atcan mi?
    ft_strcpy(key, new_item->key);
    ft_strcpy(val, new_item->value);
    new_item->next = NULL;
    return (new_item);
}

t_env *new_env()
{
    t_env *new_environment;

    new_environment = alloc(sizeof(t_env));
    if (!new_environment)
        return (NULL);
    new_environment->first_node = NULL;
    new_environment->display_text = NULL;
    return (new_environment);
}
