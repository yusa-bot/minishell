/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:24:00 by rtakayam          #+#    #+#             */
/*   Updated: 2025/04/30 15:22:25 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// #include<unistd.h>

// int main(int argc, char* argv[])
// {
// 	(void)argc;
// 	if(ft_isalpha(argv[1][0]))
// 	{
// 		write(1, "alpha", 6);
// 	}
// 	else{
// 		write(1, "not alpha", 10);
// 	}
// }