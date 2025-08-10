/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:06:08 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:39 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*p;
	size_t				i;

	i = 0;
	p = (void *) s;
	while (i < n && p[i] != (unsigned char)c)
		i++;
	if (i < n)
		return (&p[i]);
	else
		return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	// char s[20] = "HelloWorld";
// 	// printf("%p\n", ft_memchr(s, 'o', 10));
// 	// printf("%p\n", memchr(s, 'o', 10));

// 	// printf("%s\n", s);

// 	// printf("%p\n", ft_memchr(s, '\n', 2));
// 	// printf("%p\n", memchr(s, '\n', 2));

// 	// printf("%p\n", ft_memchr(s, 2+256, 3));
// 	// printf("%p\n", memchr(s, 2+256, 3));

// 	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};

// 	printf("%s", (char *)ft_memchr(tab, -1, 7));
// }