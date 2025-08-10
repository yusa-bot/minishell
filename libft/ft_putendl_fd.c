/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:42:07 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:14:50 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

// int main(int argc, char *argv[])
// {
// 	(void) argc;
// 	int fd = open("test.txt", O_WRONLY);
// 	int i = 0;
// 	while(i < argc)
// 	{
// 		ft_putendl_fd(argv[i], fd);
// 		i++;
// 	}
// }