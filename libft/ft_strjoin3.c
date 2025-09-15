/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:20:25 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 22:20:45 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    size_t len3 = ft_strlen(s3);
    char *res = malloc(len1 + len2 + len3 + 1);
    if (!res)
		return NULL;
    ft_memcpy(res, s1, len1);
    ft_memcpy(res + len1, s2, len2);
    ft_memcpy(res + len1 + len2, s3, len3);
    res[len1 + len2 + len3] = '\0';
    return res;
}
