/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:23:55 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:13:59 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *)dest;
	if (d < (unsigned char *)src)
		return (ft_memcpy(dest, src, n));
	else if (d > (unsigned char *)src)
	{
		while (n > 0)
		{
			n--;
			d[n] = ((unsigned char *)src)[n];
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char src[10] = "Helloiiii";
// 	char *p;
// 	p = src+5;
// 	ft_memmove(p, src, 7);
// 	printf("%s\n", src);

// 	char src2[10] = "Helloiiii";
// 	char *p2;
// 	p2 = src2+5;
// 	memmove(p2, src2, 7);
// 	printf("%s\n", src2);
// }