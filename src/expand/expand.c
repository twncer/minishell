/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:28:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/07/03 07:53:05 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expand.h"
#include "./../libft/libft.h"

#include <stdio.h> // debug

typedef struct s_command t_command;
typedef struct s_pos t_pos;

struct s_command
{
    char        **args;
    int         argc;
};

// struct s_pos
// {
//     int x;
//     int y;
// };

void *alloc(ssize_t size);

bool is_expander_esc_char(char ch)
{
    return (in(" '$\"", ch));
}

int valid_dollar_count(char *str)
{
    bool in_dquote;
    bool in_quote;
    int valid_dollar_counter;
    int counter;
    
    in_dquote = false;
    in_dquote = false;
    valid_dollar_counter = 0;
    counter = 0;
    while (str[counter])
    {
        if (str[counter] == '\"')
            in_dquote = !in_dquote;
        else if (str[counter] == '\'')
            in_quote = !in_quote;
        else if (str[counter] == '$' && !(!in_dquote && in_quote))
            valid_dollar_counter++;
        counter++;
    }
    return (valid_dollar_counter);
}

void insert_to_queue(char **queue, int queue_counter, char *insert)
{
    int counter;

    if (insert == NULL)
    {
        queue[queue_counter] = NULL;
        return ;
    }
    counter = 1;
    while (!is_expander_esc_char(insert[counter]) && insert[counter])
        counter++;
    printf("insert: %s | counter: %d\n", insert, counter);
    queue[queue_counter] = alloc((counter + 1) * sizeof(char));
    counter = 0;
    while ((counter == 0 && insert[counter] == '$')
        || !is_expander_esc_char(insert[counter]))
    {
        queue[queue_counter][counter] = insert[counter];
        counter++;
    }
    queue[queue_counter][counter] = '\0';
}

char **expandables_queue(char *str)
{
    bool in_dquote;
    bool in_quote;
    char **queue;
    int counter;
    int queue_counter;
    
    in_dquote = false;
    in_quote = false;
    queue = alloc((valid_dollar_count(str) + 1) * sizeof(char *));
    counter = 0;
    queue_counter = 0;
    while (str[counter])
    {
        if (str[counter] == '\"')
            in_dquote = !in_dquote;
        else if (str[counter] == '\'')
            in_quote = !in_quote;
        else if (str[counter] == '$' && !(!in_dquote && in_quote))
            insert_to_queue(queue, queue_counter++, str + counter);
        counter++;
    }
    insert_to_queue(queue, queue_counter, NULL);
    return (queue);
}

void expand_queue(char **queue)
{
    int counter;
    t_env_item *env_item;
    
    printf("\n--expanding queue--\n\n");
    counter = 0;
    while (queue[counter])
    {
        if (!queue[counter][1])
        {
            counter++;
            continue;
        }
        env_item = is_env_item_exists(queue[counter] + 1);
        if (!env_item)
            queue[counter][0] = '\0';
        else
        {
            queue[counter] = alloc((len(env_item->value) + 1) * sizeof(char));
            ft_strcpy(env_item->value, queue[counter]);
        }
        printf("after expand: %s\n", queue[counter]);
        counter++;
    }
    printf("-done-\n\n");
}
