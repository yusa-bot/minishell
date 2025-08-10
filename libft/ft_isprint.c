/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:02:36 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/02 11:36:54 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// #include<unistd.h>

// int main()
// {
// 	if(ft_isprint(' '))
// 	{
// 		write(1, "printable", 10);
// 	}
// 	else{
// 		write(1, "not printable", 14);
// 	}
// }