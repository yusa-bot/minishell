/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:31:47 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/06 21:32:00 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int builtin_echo(char **argv)
{
    int i = 1;
    int no_newline = 0;

    // -n オプションの処理（連続対応）
    while (argv[i] && strncmp(argv[i], "-n", 2) == 0 &&
           strspn(argv[i] + 2, "n") == strlen(argv[i] + 2))
    {
        no_newline = 1;
        i++;
    }

    // 引数をスペース区切りで出力
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }

    if (!no_newline)
        printf("\n");

    return 0;
}
