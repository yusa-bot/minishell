/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:59:27 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/14 14:15:29 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == INT_MIN)
		{
			ft_putchar_fd('2', fd);
			n = -147483648;
		}
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd('0' + n % 10, fd);
}

// int main()
// {
// 	int fd = open("test.txt", O_WRONLY);
// 	ft_putnbr_fd(INT_MIN, fd); //-2147483648
// 	ft_putchar_fd('\n', fd);
// 	ft_putnbr_fd(INT_MAX, fd);// 2147483647
// 	ft_putchar_fd('\n', fd);
// 	ft_putnbr_fd(0, fd);// 0
// 	ft_putchar_fd('\n', fd);
// 	ft_putnbr_fd(-45678, fd);//-45678
// 	ft_putchar_fd('\n', fd);
// }