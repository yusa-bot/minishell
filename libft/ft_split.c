/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:19:36 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:15:49 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	count_words(char const *s, char c)
{
	long long	i;
	long long	res;

	res = 0;
	i = 0;
	if (!s[0])
		return (0);
	if (s[0] != c)
		res++;
	while (s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			res++;
		i++;
	}
	return (res);
}

static long long	fill_res(char **res, long long res_index, char *ps, char c)
{
	long long	p;
	long long	len;

	p = 0;
	len = 0;
	while (ps[len] != '\0' && ps[len] != c)
		len++;
	res[res_index] = malloc(len * sizeof(char) + 1);
	if (res[res_index] == NULL)
	{
		while (res_index >= 0)
		{
			free(res[res_index]);
			res_index--;
		}
		free(res);
		return (0);
	}
	while (p < len)
	{
		res[res_index][p] = ps[p];
		p++;
	}
	res[res_index][p] = '\0';
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	long long		i;
	long long		res_index;
	long long		len;

	i = 0;
	res_index = 0;
	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			len = fill_res(res, res_index++, (char *)&s[i], c);
			if (!len)
				return (NULL);
			i += len;
		}
		else
			i++;
	}
	res[res_index] = NULL;
	return (res);
}

// #include <stdio.h>

// int main()
// {
// 	char s[] = "Maria&Rinka&&&Eishin&&";
// 	char c = '&';
// 	char **res = ft_split(s, c);
// 	printf("%zu\n", count_words(s, c));

// 	for(size_t i = 0; i <= count_words(s, c); i++)
// 		printf("%s\n", res[i]);
// }