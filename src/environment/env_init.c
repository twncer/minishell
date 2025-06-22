#include "./env.h"
#include <stdbool.h>

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
    return (env);
}

t_env *get_env()
{
    static t_env *environment = NULL;

    if (!environment)
    {
        environment = new_env();
        environment->first_node = new_env_item("__INIT__", "INIT");
    }
    return (environment);
}

#include <stdio.h>

void *init_env()
{
    t_env *env;

    env = get_env();
    if (!include_environ(env))
        return (NULL);

    printf("-- ADDIN --\n");
    add_env_item(new_env_item("NODE", "YENI_NODE"));
    add_env_item(new_env_item("NODE", "YENI_NODE2"));
    add_env_item(new_env_item("NODE", "YENI_NODE3"));
    add_env_item(new_env_item("SHLVL", "73"));
    printf("-- ADDED --\n");
    return (env);
}