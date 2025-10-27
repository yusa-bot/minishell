/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:16:55 by rinka             #+#    #+#             */
/*   Updated: 2025/10/27 14:21:11 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin_safe(char *s1, char *s2)
{
	char *new_str;
	
	if (!s1)
		return ft_strdup(s2);
	new_str= ft_strjoin(s1, s2);
	free(s1);
	return new_str;
}
