/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:17:39 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/23 09:47:22 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static int	get_digit(char c, int base)
{
	int	digit;

	digit = -1;
	if (ft_isdigit(c))
		digit = c - '0';
	else if (ft_isalpha(c))
		digit = ft_tolower(c) - 'a' + 10;
	if (digit >= base)
		return (-1);
	return (digit);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*ptr;
	long		result;
	int			sign;
	int			digit;

	ptr = nptr;
	while (*ptr == ' ' || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	sign = 1;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	result = 0;
	digit = get_digit(*ptr, base);
	while (digit >= 0)
	{
		result = result * base + digit;
		ptr++;
		digit = get_digit(*ptr, base);
	}
	if (endptr)
		*endptr = (char *)ptr;
	return (result * sign);
}
