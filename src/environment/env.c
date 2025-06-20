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
t_env *new_env();
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
    return ((ft_strcmp(key, "PWD") || ft_strcmp(key, "LINES") || ft_strcmp(key, "COLUMNS")
                || ft_strcmp(key, "__INIT__")));
}

void *include_environ(t_env *env)
{
    extern char **environ;
    char **key_val;
    int counter;
    t_env_item *curr_node;

    counter = 0;
    curr_node = env->first_node;
    while (environ[counter])
    {
        key_val = ft_split(environ[counter], '=');
        if (!key_val)
            return (NULL);
        counter++;
        if (is_ignored_env_item(key_val[0]))
            continue;
        curr_node->next = new_env_item(key_val[0], key_val[1]);
        if (!curr_node->next)
            return (NULL);
        curr_node = curr_node->next;
    }
}

t_env *init_env()
{
    t_env *environment;

    environment = new_env();
    if (!environment)
        return (NULL);
    environment->first_node = new_env_item("__INIT__", "INIT");
    if (!environment->first_node)
        return (NULL);  
    include_environ(environment);
    return (environment);
}

void print_env(t_env *env)
{
    t_env_item *node;

    node = env->first_node;
    while (node->next)
    {
        if (is_ignored_env_item(node->key))
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
