/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:37:03 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:13:39 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char s1[20] = "Hel\0le";
// 	char s2[20] = "Hel\0re";

// 	printf("%d\n", ft_memcmp(s1, s2, 5));
// 	printf("%d\n", memcmp(s1, s2, 5));

// 	printf("%d\n", ft_memcmp(s1, s2, 7));
// 	printf("%d\n", memcmp(s1, s2, 7));

// 	printf("%d\n", ft_memcmp(s2, s1, 6));
// 	printf("%d\n", memcmp(s2, s1, 6));

// 	char s3[20] = "Hello";
// 	char s4[20] = "Hello";

// 	printf("%d\n", ft_memcmp(s3, s4, 5));
// 	printf("%d\n", memcmp(s3, s4, 5));

// 	printf("%d\n", ft_memcmp(s3, s4, 10));
// 	printf("%d\n", memcmp(s3, s4, 10));

// }