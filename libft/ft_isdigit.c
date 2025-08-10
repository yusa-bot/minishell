/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:25:50 by rtakayam          #+#    #+#             */
/*   Updated: 2025/05/02 11:31:35 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// #include<unistd.h>

// int main(int argc, char* argv[])
// {
// 	(void)argc;
// 	if(ft_isdigit(argv[1][0] - '0'))
// 	{
// 		write(1, "digit", 6);
// 	}
// 	else{
// 		write(1, "not digit", 10);
// 	}
// }