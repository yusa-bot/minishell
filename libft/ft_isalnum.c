/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:29:59 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/07 12:19:11 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// #include<unistd.h>

// int main()
// {
// 	if(ft_isalnum('0'))
// 	{
// 		write(1, "alnum", 6);
// 	}
// 	else{
// 		write(1, "not alnum", 10);
// 	}
// }