/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:15:07 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/23 09:46:18 by ayusa            ###   ########.fr       */
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
