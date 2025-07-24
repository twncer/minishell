/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:28:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/07/19 18:39:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../libft/libft.h"
#include "./expand.h"
#include <stdio.h> // debug

typedef struct s_command t_command;

struct s_command
{
    char        **args;
    int         argc;
};

void *alloc(ssize_t size);

bool is_expander_esc_char(char ch)
{
    return (in(" '$\"", ch));
}

int quote_status(char *str, int index)
{
    bool in_quote;
    bool in_dquote;
    char inner_quote_type;
    int counter;
    
    in_quote = false;
    in_dquote = false;
    counter = 0;
    while(str[counter])
    {
        if (counter == index)
        {
            // "'$HOME'"
            if (in_quote && in_dquote && inner_quote_type == '\"')
                return (-1);
            if (!(!in_dquote && in_quote))
                return (1);
        }
        if (in("\'\"", str[counter]))
            inner_quote_type = str[counter];
        if (str[counter] == '\'')
            in_quote = !in_quote;
        else if (str[counter] == '\"')
            in_dquote = !in_dquote;
        counter++;
    }
    return (-1);
}

bool in_any_quote(char *str, int index)
{
    bool in_quote;
    bool in_dquote;
    int counter;

    in_quote = false;
    in_dquote = false;
    counter = 0;
    while (str[counter])
    {
        if (str[counter] == '\'')
            in_quote = !in_quote;
        else if (str[counter] == '\"')
            in_dquote = !in_dquote;
        if (counter == index)
        {
            // expandlenecekse true;
            if (str[index] == '\'' && in_quote && !in_dquote)
                return (true);
            else if (str[index] == '\"' && in_dquote && !in_quote)
                return (true);
            else if (str[index] == '\'' && !in_quote && !in_dquote)
                return (true);
            else if (str[index] == '\"' && !in_dquote && !in_quote)
                return (true);
            else
                return (false);
        }
        counter++;
    }
    return (false);
}

int valid_dollar_count(char *str)
{
    int valid_dollar_counter;
    int counter;
    
    printf("im here 2\n");
    valid_dollar_counter = 0;
    counter = 0;
    while (str[counter])
    {
        if (str[counter] == '$' && quote_status(str, counter) == 1)
            valid_dollar_counter++;
        counter++;
    }
    printf("\nVALID DOLLAR COUNT: %d\n", valid_dollar_counter);
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
    while (insert[counter] && !is_expander_esc_char(insert[counter]))
        counter++;
    printf("insert: %s | counter: %d\n", insert, counter);
    get_expander(0)->old_len += counter;
    queue[queue_counter] = alloc((counter + 1) * sizeof(char));
    if (is_expander_esc_char(insert[1]))
    {
        queue[queue_counter][0] = '\0';
        return ;
    }
    counter = 0;
    while (insert[counter]
            && ((counter == 0 && insert[counter] == '$')
                || !is_expander_esc_char(insert[counter])))
    {
        queue[queue_counter][counter] = insert[counter];
        counter++;
    }
    queue[queue_counter][counter] = '\0';
}

char **queue_expandables(char *str)
{
    int counter;
    int queue_counter;
    
    get_expander(1)->queue = alloc((valid_dollar_count(str) + 1) * sizeof(char *));
    counter = 0;
    queue_counter = 0;
    while (str[counter])
    {
        if (str[counter] == '$' && quote_status(str, counter) == 1)
            insert_to_queue(get_expander(0)->queue, queue_counter++, str + counter);
        counter++;
    }
    insert_to_queue(get_expander(0)->queue, queue_counter, NULL);
    return (get_expander(0)->queue);
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
            get_expander(0)->new_len += len(queue[counter]);
        }
        printf("after expand: %s\n", queue[counter]);
        counter++;
    }
    printf("-done-\n\n");
}

void implement_queue(char **prompt, char **queue)
{
    char *new_prompt;
    int new_prompt_counter;
    int prompt_counter;
    int queue_counter;

    new_prompt = alloc((len((*prompt)) - get_expander(0)->old_len
            + get_expander(0)->new_len + 1) * sizeof(char));
    new_prompt_counter = 0;
    prompt_counter = 0;
    queue_counter = 0;
    while ((*prompt)[prompt_counter])
    {
        if (in("\'\"", (*prompt)[prompt_counter]) && in_any_quote(*prompt, prompt_counter))
            prompt_counter++;
        else if ((*prompt)[prompt_counter] == '$' && quote_status((*prompt), prompt_counter) == 1)
        {
            printf("im here\n");
            ft_strcpy((get_expander(0)->queue)[queue_counter], new_prompt + new_prompt_counter);
            new_prompt_counter += len(queue[queue_counter]); 
            queue_counter++;
            prompt_counter++;
            while (!is_expander_esc_char((*prompt)[prompt_counter]) && (*prompt)[prompt_counter])
                prompt_counter++;
        }
        else
        {
            new_prompt[new_prompt_counter] = (*prompt)[prompt_counter];
            new_prompt_counter++; prompt_counter++;
        }
    }
    new_prompt[new_prompt_counter] = '\0';
    (*prompt) = new_prompt;
}
