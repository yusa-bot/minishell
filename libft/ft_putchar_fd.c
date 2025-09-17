/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:20:58 by rtakayam          #+#    #+#             */
/*   Updated: 2025/09/17 22:10:05 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_putchar_fd(char c, int fd)
{
    if (write(fd, &c, 1) < 0)
        return (-1);
    return (1);
}

// int main()
// {
// 	int fd = open("test.txt", O_WRONLY);
// 	ft_putchar_fd('A', fd);
// 	ft_putchar_fd('c', fd);
// 	ft_putchar_fd('B', fd);
// }