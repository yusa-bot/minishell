/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_oneptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:03:56 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/26 11:24:19 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin_oneptr(char *s1, char *s2)
{
	char *new_str;

	if (!s1)
		return (ft_strdup(s2));
	new_str= ft_strjoin(s1, s2);
	return (new_str);
}
