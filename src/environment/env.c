/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:35:35 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/20 20:38:39 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"
#include "./../libft/libft.h"
#include "stdlib.h"

#include <stdio.h>

t_env_item *is_env_item_exists(char *key)
{
    t_env_item *node;

    node = get_env()->first_node;
    while (node)
    {
        if (ft_strcmp(node->key, key) && printf("gotcha!\n"))
            return (node);
        node = node->next;
    }
    return (NULL);
}

t_env_item *add_env_item(t_env_item *new_item)
{
    t_env_item *node;
    t_env_item *node_exists;

    node = get_env()->first_node;

    node_exists = is_env_item_exists(new_item->key);
    if (node_exists)
    {
        node_exists->value = new_item->value;
        return (new_item);
    }
    
    while (node->next)
        node = node->next;
    node->next = new_item;
    return (node);
}

void print_env()
{
    t_env_item *node;

    node = get_env()->first_node;
    while (node)
    {
        if (ft_strcmp(node->key, "__INIT__"))
        {
            node = node->next;
            continue;
        }
        write(1, node->key, len(node->key));
        write(1, ": ", 2);
        write(1, node->value, len(node->value));
        write(1, "\n", 1);
        node = node->next;
    }
}
