/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:13:06 by btuncer           #+#    #+#             */
/*   Updated: 2025/06/17 18:02:56 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H
# include <stdbool.h>
# include <sys/types.h>

bool is_str_empty(char *str);
bool	in(char *str, char c);
ssize_t	len(char *str);
void ft_strcpy(char *src, char *dst);
bool ft_strcmp(char *str, char *to_cmp);
char	**ft_split(char const *s, char c);

#endif