/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:00:35 by rtakayam          #+#    #+#             */
/*   Updated: 2025/04/30 15:24:01 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char s[20] = "HelloWorld";
// 	printf("%s\n", s);
// 	ft_bzero(s, 5);
// 	printf("%s\n", s);
// 	printf("%s\n", s+5);
// 	printf("%s\n", s+6);

// 	char s2[20] = "HelloWorld";
// 	printf("%s\n", s2);
// 	bzero(s2, 5);
// 	printf("%s\n", s2);
// 	printf("%s\n", s2+5);
// 	printf("%s\n", s2+6);
// }