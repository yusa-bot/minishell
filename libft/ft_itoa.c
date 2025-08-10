/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:37 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/15 09:47:01 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

static int	cal_digit(int n)
{
	int	res;

	res = 1;
	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		n = -n;
		res += 1;
	}
	while (n > 9)
	{
		res++;
		n /= 10;
	}
	return (res);
}

static void	locate_nums(int n, int sign, char *res, int digit)
{
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	while (digit - 1 >= sign)
	{
		res[digit - 1] = n % 10 + '0';
		n /= 10;
		digit--;
	}
	if (sign == 1)
		res[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*res;
	int		digit;
	int		sign;

	digit = cal_digit(n);
	sign = 0;
	res = malloc((digit + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[digit] = '\0';
	if (n == INT_MIN)
	{
		locate_nums(-214748364, sign, res, 10);
		res[10] = '8';
		return (res);
	}
	locate_nums(n, sign, res, digit);
	return (res);
}

// #include <stdio.h>

// int main()
// {
// 	// printf("%d\n", cal_digit(2147483647));
// 	// printf("%d\n", INT_MIN);
// 	printf("%s\n", ft_itoa(-123456));
// 	printf("%s\n", ft_itoa(INT_MAX));
// 	printf("%s\n", ft_itoa(INT_MIN));
// 	printf("%s\n", ft_itoa(0));
// }