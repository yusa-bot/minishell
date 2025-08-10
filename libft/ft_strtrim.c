/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:51:54 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:16:44 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ret_null(void)
{
	char	*res;

	res = malloc(1);
	if (res == NULL)
		return (NULL);
	*res = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	size_t		begin;
	size_t		end;
	size_t		i;

	begin = 0;
	if (ft_strlen(s1) == 0)
		return (ret_null());
	end = ft_strlen(s1) - 1;
	while (s1[begin] && begin < ft_strlen(s1) && is_set(s1[begin], set))
		begin++;
	if (!s1[begin])
		return (ret_null());
	while (end && is_set(s1[end], set))
		end--;
	res = malloc((end - begin + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
		res[i++] = s1[begin++];
	res[i] = '\0';
	return (res);
}

// #include <stdio.h>

// int main()
// {
// 	char s1[] = "&@&000 @&& 000&@&";
// 	char set[] = "@&";
// 	printf("%s\n", ft_strtrim(s1, set));
// }