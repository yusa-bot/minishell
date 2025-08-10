/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:06:56 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/07 12:23:37 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int	gap;

	gap = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		c -= gap;
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