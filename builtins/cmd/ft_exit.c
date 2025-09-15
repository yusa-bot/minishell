/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:32:04 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 12:46:52 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//直前のコマンドの終了ステータス（g_last_status）

int ft_exit(char **argv)
{
	int argc;
	int exit_status;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		write(2, "exit: too many arguments\n", 26);
		return 1;
	}
	if (argc == 2)
	{
		char *endptr;
		long val = ft_strtol(argv[1], &endptr, 10);//long変換
		if (*endptr != '\0' || val < 0 || val > 255) //対象外
		{
			write(2, "exit: numeric argument required\n", 34);
			exit(255); //非数値
		}
		exit_status = (int)(val % 256); // 終了ステータスは0-255の範囲に収める
	}
	else
		exit_status = 0;
	printf("exit\n");
	exit(exit_status);
}
