/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:45:41 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/09 14:28:42 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	// char s1[20] = "Hell\0o";
// 	// char s2[20] = "HelloWorld";

// 	// printf("%d\n", ft_strncmp(s1, s2, 5));
// 	// printf("%d\n", strncmp(s1, s2, 5));

// 	// printf("%d\n", ft_strncmp(s1, s2, 7));
// 	// printf("%d\n", strncmp(s1, s2, 7));

// 	// printf("%d\n", ft_strncmp(s2, s1, 6));
// 	// printf("%d\n", strncmp(s2, s1, 6));

// 	// char s3[20] = "Hello";
// 	// char s4[20] = "Hello";

// 	// printf("%d\n", ft_strncmp(s3, s4, 5));
// 	// printf("%d\n", strncmp(s3, s4, 5));

// 	printf("%d\n", ft_strncmp("\200", "\0", 2));
// 	printf("%d\n", strncmp("\200", "\0", 2));

// }