/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:10:38 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/23 20:00:19 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/types.h>

bool is_str_empty(char *str)
{
    int counter;
    bool is_empty;
    
    counter = 0;
    is_empty = true;
    while (str[counter] && is_empty)
    {
        if (str[counter] != ' ')
            is_empty = false;
        counter++;
    }
    return (is_empty);
}

bool	in(char *str, char c)
{
	ssize_t	counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] == c)
			return (true);
		counter++;
	}
	return (false);
}

ssize_t	len(char *str)
{
	ssize_t	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

void ft_strcpy(char *src, char *dst)
{
	ssize_t counter;

	counter = 0;
	while (counter < len(src))
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
}

bool ft_strcmp(char *str, char *to_cmp)
{
	int counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] != to_cmp[counter])
			return (false);
		counter++;
	}
	return (true);
}

void increase_istr(char *str)
{
	char *last_digit = str + len(str) - 1;
	if ((*last_digit) == '9')
	{
		(*last_digit) = '0'; // yok bu iş böyle olmaz buna bir ara atoi itoa yaz
	}
	else
		(*last_digit) += 1;
}