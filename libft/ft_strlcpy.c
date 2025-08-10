/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:00:46 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:17 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char src[20] = "ii";
// 	char dest[6] = "Hello";
// 	size_t rv;
// 	rv = ft_strlcpy(dest, src, 1);
// 	printf("%zu\n", rv);
// 	printf("%s\n", dest);

// 	// char dest2[20] = "He";
// 	// size_t rv2;
// 	// rv2 = strlcpy(dest2, src, 5);
// 	// printf("%s\n", dest2);x
// }