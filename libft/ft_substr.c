/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:16:28 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:50 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_null(void)
{
	char	*res;

	res = malloc(1);
	if (res == NULL)
		return (NULL);
	*res = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (return_null());
	while (s[start + i])
		i++;
	if (i < len)
		len = i;
	i = 0;
	res = malloc((len) * sizeof(char) + 1);
	if (res == NULL)
		return (NULL);
	while (s[start] && i < (unsigned int)len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

// #include <stdio.h>

// int main()
// {
// 	// char src[] = "HelloWo\0rld";
// 	// char *res = ft_substr("Bonjour comment ca va?", 5, 8);
// 	printf("%s\n", ft_substr("tripouille", 0, 42000));
// }