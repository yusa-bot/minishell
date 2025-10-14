/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:12:13 by rinka             #+#    #+#             */
/*   Updated: 2025/10/14 22:15:39 by rinka            ###   ########.fr       */
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
		ft_free_str_array(arr);
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
		ft_free_str_array(res);
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
	res = ft_strjoin_safe(res, "_");
	if (res == NULL)
		return(free_hdfile_info(tty_str, counter_str));
	res = ft_strjoin_safe(res, counter_str);
	if (res == NULL)
		return(free_hdfile_info(tty_str, counter_str));
	free(tty_str);
	free(counter_str);
	return (res);
}


char *ft_heredoc(char *eof, t_cmd *cmd_lst, t_env *env_lst, char ***tmpfiles)
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
			malloc_error(NULL, &cmd_lst, &env_lst, NULL);
	}
	// printf("hd_fn : %s\n", hd_filename);//////
	hd_fd = open(hd_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (hd_fd == -1)//openエラー
	{
		perror(hd_filename);
		// g_exit_status = 1;
		close(hd_fd);
		ft_cmdlst_clear(&cmd_lst);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
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
	*tmpfiles = ft_strarr_add(*tmpfiles, hd_filename);
	return (hd_filename);
}

//current: makeできるが実行チェックまだ