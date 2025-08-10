/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:52:44 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:35 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char		*b;
	char		*l;
	size_t		l_len;
	size_t		i;

	if (little[0] == '\0')
		return ((char *)big);
	b = (char *) big;
	l = (char *) little;
	l_len = ft_strlen(l);
	if (len == 0 || len < l_len)
		return (NULL);
	i = 0;
	while (i <= len - l_len)
	{
		if (*b == l[0] && ft_strncmp(b, l, l_len) == 0)
			return (b);
		if (!*(b + 1))
			break ;
		b++;
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// char *ex_strnstr(const char *s1, const char *s2, size_t n)
// {
// 	size_t i, len;
// 	char c = *s2;

// 	if (c == '\0')
// 		return (char *)s1;

// 	for (len = ft_strlen(s2); len <= n && *s1; n--, s1++)
// 	{
// 		if (*s1 == c)
// 		{
// 			for (i = 1;; i++)
// 			{
// 				if (i == len)
// 					return (char *)s1;
// 				if (s1[i] != s2[i])
// 					break;
// 			}
// 		}
// 	}
// 	return NULL;
// }

// int main()
// {
// 	char haystack[30] = "abcdefgh";
// 	// char * empty = (char*)"";
// 	printf("%p\n", ft_strnstr(haystack, "abc", 2));
// 	printf("%p\n", ex_strnstr(haystack, "abc", 2));

// 	return (0);
// }