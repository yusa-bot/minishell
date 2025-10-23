/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:36:56 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/23 09:44:57 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_putstr_fd(char *s, int fd)
{
    size_t i;

    if (!s)
        return (0);
    i = 0;
    while (s[i] != '\0')
    {
        if (ft_putchar_fd(s[i], fd) < 0)
            return (-1); // write失敗を伝える
        i++;
    }
    return (i); // 書き込んだ文字数（または成功フラグとして 0 でもOK）
}

// int main(int argc, char *argv[])
// {
// 	(void) argc;
// 	int fd = open("test.txt", O_WRONLY);
// 	int i = 0;
// 	while(i < argc)
// 	{
// 		ft_putstr_fd(argv[i], fd);
// 		i++;
// 	}
// }
