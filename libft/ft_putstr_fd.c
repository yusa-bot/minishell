/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:36:56 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:15:37 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

// int main(int argc, char *argv[])
// {
// 	(void) argc;
// 	int fd = open("test.txt", O_WRONLY);
// 	int i = 0;
// 	while(i < argc)
// 	{
// 		ft_putstr_fd(argv[i], fd);
// 		i++;
// 	}
// }