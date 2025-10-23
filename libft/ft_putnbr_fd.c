/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:59:27 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/23 09:44:08 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_negative(int *n, int fd)
{
	int	count;

	count = 0;
	if (*n < 0)
	{
		if (ft_putchar_fd('-', fd) < 0)
			return (-1);
		count++;
		if (*n == INT_MIN)
		{
			if (ft_putchar_fd('2', fd) < 0)
				return (-1);
			count++;
			*n = -147483648;
		}
		*n = -*n;
	}
	return (count);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	count;
	int	tmp;

	count = handle_negative(&n, fd);
	if (count < 0)
		return (-1);
	if (n > 9)
	{
		tmp = ft_putnbr_fd(n / 10, fd);
		if (tmp < 0)
			return (-1);
		count += tmp;
	}
	if (ft_putchar_fd('0' + n % 10, fd) < 0)
		return (-1);
	return (count + 1);
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
