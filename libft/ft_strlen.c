/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:04:42 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:22 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (s[res])
	{
		res++;
	}
	return (res);
}

// #include <stdio.h>

// int main(int argc, char *argv[])
// {
// 	(void) argc;
// 	printf("%zu", ft_strlen(argv[1]));
// 	return (0);
// }