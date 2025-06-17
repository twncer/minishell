/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:35:35 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/17 19:13:32 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> // aa
#include <unistd.h> // aa
#include <sys/types.h> // for len()
#include "./env.h"
#include "./../libft/libft.h"

ssize_t len(char *);
void *alloc(ssize_t);
char	**ft_split(char const *s, char c);
t_env_item *new_env_item(char *key, char *val);
char	**free_all(char **splitted, unsigned int count);
char *get_cwd();

char **fetch_env_item(char *item_name)
{
    char **env_item;

    env_item = alloc(2 * sizeof(char *));
    if (!env_item)
        return (NULL);
    env_item[0] = alloc(len(item_name) * sizeof(char));
    if (!env_item[0])
        return (NULL);
    env_item[0] = item_name;
    env_item[1] = getenv(item_name);
    if (!env_item[1])
        return (NULL);
    return (env_item);
}

bool is_ignored_env_item(char *key)
{
    return ((ft_strcmp(key, "PWD") || ft_strcmp(key, "LINES") || ft_strcmp(key, "COLUMNS")));
}

t_env *init_env()
{
    t_env *environment;
    t_env_item *current_env_item;
    t_env_item *env_item;
    extern char **environ;
    char **key_val;
    
    environment = alloc(sizeof(environment));
    environment->first_node = NULL;
	while (*environ)
	{
		key_val = ft_split(*environ, '=');
		if (is_ignored_env_item(key_val[0]))
        {
            environ++;
            continue;
        }
        env_item = new_env_item(key_val[0], key_val[1]);

        if (environment->first_node == NULL) {
            environment->first_node = env_item;
            current_env_item = env_item;
        } else {
            current_env_item->next = env_item;
            current_env_item = current_env_item->next;
        }
        environ++;
	}

    t_env_item *new_item = new_env_item("burak", "tuncer");
    current_env_item->next = new_item;

    return (environment);
}

void print_env(t_env *env)
{
    t_env_item *node;

    node = env->first_node;
    while (node->next)
    {
        write(1, node->key, len(node->key));
        write(1, ": ", 2);
        write(1, node->value, len(node->value));
        write(1, "\n", 1);
        node = node->next;
    }
}
