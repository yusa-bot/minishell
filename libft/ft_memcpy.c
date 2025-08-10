/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:07:00 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:13:47 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	const char		*s;
	size_t			i;

	if (!dest && !src)
		return (dest);
	s = src;
	d = dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// int main()
// {
// 	// char src[20] = "iiiiiiiiiiiii";
// 	// char dest[20] = "He";
// 	// ft_memcpy(dest, src, 5);
// 	// printf("%s\n", dest);

// 	// char dest2[20] = "He";
// 	// memcpy(dest2, src, 5);
// 	// printf("%s\n", dest2);

// 	// char src[20] = "Helloiiii";//出力"zyxwvutjjjjjjjjjjjjjjj"
// 	char p[40] = "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
// 	printf("%s\n", p);
// 	ft_memcpy(p, "zy\0xw\0vu\0\0tsr", 11);
// 	write(1, p, 30);

// 	// char src2[20] = "Helloiiii";//出力"HelloHelloii"
// 	// char *p2;
// 	// p2 = src2+5;
// 	// memmove(p2, src2, 7);
// 	// printf("%s\n", src2);
// }