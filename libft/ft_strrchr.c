/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:38:11 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:39 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	size_t	i;

	i = ft_strlen(s);
	p = (char *) s;
	while (p[i] != (unsigned char)c && i != 0)
		i--;
	if (p[i] != (unsigned char)c)
		return (NULL);
	return (&p[i]);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char s[20] = "Hel\0loWorld";
// 	printf("%p\n", ft_strrchr(s, 'o'));
// 	printf("%p\n", strrchr(s, 'o'));

// 	printf("%s\n", s);

// 	printf("%s\n", ft_strrchr(s, 'l'));
// 	printf("%s\n", strrchr(s, 'l'));

// 	printf("%p\n", ft_strrchr(s, '\0'));
// 	printf("%p\n", strrchr(s, '\0'));
// }