/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:06:56 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/02 10:21:16 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	int	gap;

	gap = 'a' - 'A';
	if (c >= 'A' && c <= 'Z')
		c += gap;
	return (c);
}

// #include <stdio.h>

// int main(int argc, char *argv[])
// {
// 	(void)argc;
// 	int i = 0;
// 	while(argv[1][i])
// 	{
// 		argv[1][i] = ft_toupper(argv[1][i]);
// 		i++;
// 	}
// 	printf("%s\n", argv[1]);
// }