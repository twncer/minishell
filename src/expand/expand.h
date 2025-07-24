/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:27:16 by btuncer           #+#    #+#             */
/*   Updated: 2025/07/18 16:12:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../environment/env.h"

typedef struct s_expander t_expander;

struct s_expander {
    bool is_default;
    char **queue;
    int old_len;
    int new_len;
};

t_expander *new_expander();
t_expander *get_expander(bool recreate);
