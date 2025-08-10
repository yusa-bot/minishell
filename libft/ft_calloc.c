/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:19:35 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:13 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;
	size_t			i;
	size_t			p;

	i = 0;
	p = nmemb * size;
	if (size > 0 && p / size != nmemb)
		return (NULL);
	res = malloc(nmemb * size);
	if (res == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

// #include <stdio.h>

// int main()
// {
// 	void *res;

// 	// printf("%p\n", res);

// 	res = ft_calloc(SIZE_MAX, SIZE_MAX);

// 	printf("%p\n", res);
// }