/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:16:52 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:15:54 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	if ((unsigned char)c == 0 && p[i] == '\0')
		return (&p[i]);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char s[20] = "teste";
// 	printf("%p\n", ft_strchr(s, 1024));
// 	printf("%p\n", strchr(s, 1024));

// // 	printf("%s\n", s);

// // 	printf("%s\n", ft_strchr(s, 't'));
// // 	printf("%s\n", strchr(s, 't'));

// // 	printf("%p\n", ft_strchr(s, 'l'));
// // 	printf("%p\n", strchr(s, 'l'));
// }