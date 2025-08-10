/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:10:57 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/07 12:21:52 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

// #include <stdio.h>

// int main()
// {
// 	void (*f)(unsigned int, char*);
// 	char s[] = "0000000";
// 	f = to_index;

// 	ft_striteri(s, f);
// 	printf("%s\n", s);
// }