/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:31:47 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/25 17:16:43 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_echo(char **argv, int fd)
{
    int i = 1;
    int no_newline = 0;
    // -nを"-nnn"や"-n -n"に対応
    while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0 &&
           ft_strspn(argv[i] + 2, "n") == ft_strlen(argv[i] + 2))
    {
        no_newline = 1;
        i++;
    }
    //複数引数
    while (argv[i])
    {
		if (ft_putstr_fd(argv[i], fd) < 0)
            perror_exit("minishell: echo");
		if (argv[i + 1] && ft_putstr_fd(" ", fd) < 0)
            perror_exit("minishell: echo");
        i++;
    }
	if (!no_newline && ft_putstr_fd("\n", fd) < 0)
         perror_exit("minishell: echo");
    return (EXIT_SUCCESS);
}


//#include <stdio.h>
//int main()
//{
//    printf("=== ft_echo テスト ===\n\n");

//    // テスト1: 基本的な出力
//    printf("テスト1: 基本出力\n");
//    char *test1[] = {"echo", "hello", "world", NULL};
//    ft_echo(test1);
//    printf("期待値: hello world\\n\n");

//    // テスト2: -nオプション
//    printf("テスト2: -nオプション\n");
//    char *test2[] = {"echo", "-n", "no", "newline", NULL};
//    ft_echo(test2);
//    printf(" <-- 改行なし\n期待値: no newline <-- 改行なし\n\n");

//    // テスト3: -nnオプション
//    printf("テスト3: -nnオプション\n");
//    char *test3[] = {"echo", "-nn", "test", NULL};
//    ft_echo(test3);
//    printf(" <-- 改行なし\n期待値: test <-- 改行なし\n\n");

//    // テスト4: 複数の-nオプション
//    printf("テスト4: 複数の-nオプション\n");
//    char *test4[] = {"echo", "-n", "-nn", "multiple", NULL};
//    ft_echo(test4);
//    printf(" <-- 改行なし\n期待値: multiple <-- 改行なし\n\n");

//    // テスト5: 無効なオプション
//    printf("テスト5: 無効なオプション\n");
//    char *test5[] = {"echo", "-na", "invalid", NULL};
//    ft_echo(test5);
//    printf("期待値: -na invalid\\n\n");

//    // テスト6: 引数なし
//    printf("テスト6: 引数なし\n");
//    char *test6[] = {"echo", NULL};
//    ft_echo(test6);
//    printf("期待値: (空行)\\n\n");

//    return 0;
//}
