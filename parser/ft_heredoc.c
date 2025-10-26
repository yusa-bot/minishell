/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:12:13 by rinka             #+#    #+#             */
/*   Updated: 2025/10/25 22:03:21 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_strarr_add(char **arr, char *new_str)
{
	char **res;
	int i;

	i = 0;
	while (arr && arr[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if(res == NULL)
	{
		free_split(arr);
		return (NULL);
	}
	i = 0;
	while (arr && arr[i])
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = ft_strdup(new_str);
	if(res[i] == NULL)
	{
		free_split(res);
		free(arr);
		return (NULL);
	}
	res[i + 1] = NULL;
	free(arr);
	return (res);
}

static void *free_hdfile_info(char *tty_str, char*counter_str)
{
	if (tty_str)
		free(tty_str);
	if	(counter_str)
		free(counter_str);
	return (NULL);
}

char *create_heredoc_filename(void) //呼び出し元でaccessチェック→既に存在していれば再試行
{
	char *res;
	int tty_slot_id;
	char *tty_str;
	static int counter;
	char *counter_str;

	counter++;
	res = NULL;
	tty_slot_id = ttyslot();
	tty_str = ft_itoa(tty_slot_id);
	if (!tty_str)
		return (NULL);
	counter_str = ft_itoa(counter);
	if (!counter_str)
		return(free_hdfile_info(tty_str, NULL));
	res = ft_strjoin("/tmp/.hd_", tty_str);
	if (res == NULL)
		return(free_hdfile_info(tty_str, counter_str));
	res = ft_strjoin_oneptr(res, "_");
	if (res == NULL)
		return(free_hdfile_info(tty_str, counter_str));
	res = ft_strjoin_oneptr(res, counter_str);
	if (res == NULL)
		return(free_hdfile_info(tty_str, counter_str));
	free(tty_str);
	free(counter_str);
	return (res);
}


char	*ft_heredoc(t_shell *sh, char *eof)
{
	char *hd_filename;
	int hd_fd;
	char *line;

	hd_filename = NULL;
	while (!hd_filename || access(hd_filename, F_OK) == 0)
	{
		if (hd_filename)
			free(hd_filename);
		hd_filename = create_heredoc_filename();
		if (!hd_filename)
			malloc_error(sh, NULL);
	}
	// printf("hd_fn : %s\n", hd_filename);//////
	hd_fd = open(hd_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (hd_fd == -1)//openエラー
	{
		perror(hd_filename);
		// g_exit_status = 1;
		close(hd_fd);
		ft_cmdlst_clear(&sh->cmd);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)//Ctrl-C ////////////編集する。 //「入力を中断してシェルに戻る」
		{
			printf("SIGINT\n");
			g_sig = 0; //0/2 どっち？
			free(line);
			//readline() は内部でエラー復帰する（rl_done などで）
			//		ループ側で if (g_signal == SIGINT) を検出 -> その時点で安全にメモリをfreeして、新しいプロンプトを出す
			continue;
		}
		//Ctrl-D（EOF）で入力が終了した場合 →
		//bash と同じように「warning: here-document delimited by end-of-file (wanted'EOF')」を出すか、そのまま終了
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		write(hd_fd, line, ft_strlen(line));
		write(hd_fd, "\n", 1);
		free(line);
	}
	close(hd_fd);
	sh->tmpfiles = ft_strarr_add(sh->tmpfiles, hd_filename);
	return (hd_filename);
}

//current: makeできるが実行チェックまだ
