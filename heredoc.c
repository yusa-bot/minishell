/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:40:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/27 20:35:52 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *unquote_all(const char *src)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!src)
		return (NULL);
	len = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] != '\'' && src[i] != '"')
			len++;
		i++;
	}
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] != '\'' && src[i] != '"')
		{
			res[j] = src[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

// delimiterまで読み込み、pipeのread側FDを返す。失敗時 -1
static int build_heredoc_fd(const char *delim_arg, int do_expand, void *env)
{
    int fds[2];
    char *line = NULL;
    char *delim = NULL;

    if (pipe(fds) < 0)
		return -1;

    g_sig = 0;

    delim = unquote_all(delim_arg);
	if (!delim)
	{
		close(fds[0]);
		close(fds[1]);
		return -1;
	}

    while (!g_sig)
	{
        line = readline("> ");
        if (!line)
			break;
        if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}

        char *out = NULL;
        if (do_expand)
			out = expand_vars(line, env);//置き換える
        else
			out = ft_strdup(line);
        free(line);
		line = NULL;
        if (!out)
		{
			g_sig = 1;
			break;
		}

        // 行+改行を書き込む
        write(fds[1], out, strlen(out));
        write(fds[1], "\n", 1);
        free(out);
    }

    free(delim);
    close(fds[1]);

    if (g_sig)
	{
        close(fds[0]);
        return -1;
    }
    return fds[0];
}

// クォートあり→展開しない
int is_quoted_delim(const char *delim)
{
    if (!delim || !*delim)
        return (0);
    int len = ft_strlen(delim);
    if (len >= 2)
    {
        if ((delim[0] == '\'' && delim[len-1] == '\'') ||
            (delim[0] == '"' && delim[len-1] == '"'))
            return (1);
    }
    return (0);
}


//ここではｒを回す。
int prepare_heredoc_for_cmd(t_cmd *cmd, void *env)
{
	t_redirect *r = cmd->infile;
    while (r)
	{
		if (r->token_type == HEREDOC)
		{
			int expand = !is_quoted_delim(r->original_str);
            int fd = build_heredoc_fd(r->original_str, expand, env);
            if (fd < 0)
				return -1;
            r->prepared_fd = fd;
            r->token_type = INFILE;
        }
		r = r->next;
    }
    return 0;
}

////

// extern int g_signal; // SIGINT キャッチ用 (global 1つだけ OK)

// /**
//  * 環境変数展開関数のダミー
//  * 実際は $VAR / $? の展開を自前で書く
//  */
// static char *expand_line(char *line, t_env *env)
// {
//     // TODO: $VAR, $? 展開処理
//     (void)env;
//     return line;
// }

// /**
//  * heredoc 入力を処理して pipe の read end を返す
//  * delimiter: 区切り文字列
//  * quoted   : delimiter がクオートされているか (1なら展開無効)
//  */
// int run_heredoc(char *delimiter, int quoted, t_env *env)
// {
//     int     pipefd[2];
//     char    *line;

//     if (pipe(pipefd) == -1)
//     {
//         perror("pipe");
//         return (-1);
//     }

//     // 子プロセスを作って heredoc 入力を処理する (bash と同じ動き)
//     pid_t pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         close(pipefd[0]);
//         close(pipefd[1]);
//         return (-1);
//     }
//     if (pid == 0)
//     {
//         // child: heredoc 入力ループ
//         signal(SIGINT, SIG_DFL); // Ctrl-C はここで効くようにする
//         close(pipefd[0]);        // 読み込み側は使わない
//         while (1)
//         {
//             line = readline("> ");
//             if (!line) // Ctrl-D / EOF
//             {
//                 fprintf(stderr,
//                         "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
//                         delimiter);
//                 break;
//             }
//             if (ft_strcmp(line, delimiter) == 0)
//             {
//                 free(line);
//                 break;
//             }
//             if (!quoted)
//                 line = expand_line(line, env);
//             write(pipefd[1], line, ft_strlen(line));
//             write(pipefd[1], "\n", 1);
//             free(line);
//         }
//         close(pipefd[1]);
//         exit(0);
//     }
//     else
//     {
//         // parent
//         int status;
//         close(pipefd[1]); // 書き込み側は親では不要
//         waitpid(pid, &status, 0);
//         if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
//         {
//             // Ctrl-C で中断した場合
//             close(pipefd[0]);
//             return (-1);
//         }
//         return pipefd[0]; // 読み込み側を返す
//     }
// }
