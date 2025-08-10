/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:00:46 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:13 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	while (src[i] && i < size - dest_len - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char src[20] = "iiiiii";
// 	char dest[] = "Hello";
// 	size_t rv;
// 	rv = ft_strlcat(dest, src, 3);
// 	printf("%zu\n", rv);
// 	printf("%s\n", dest);

// 	// char dest2[20] = "He";
// 	// size_t rv2;
// 	// rv2 = strlcpy(dest2, src, 5);
// 	// printf("%s\n", dest2);x
// }