/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:45:56 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/17 19:00:53 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./../libft/libft.h"

typedef struct s_environment t_env;
typedef struct s_environment_item t_env_item;

struct s_environment
{
    t_env_item *first_node;
    char *display_text;
};

struct s_environment_item
{
    char *key;
    char *value;
    t_env_item *next;
};

t_env_item *new_env_item(char *key, char *val);
t_env *new_env();
t_env *get_env();
t_env_item *add_env_item(t_env_item *new_item);