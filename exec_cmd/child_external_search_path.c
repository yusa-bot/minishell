/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_external_search_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:45:01 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/29 18:54:27 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		perror_exit("malloc");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

// PATH環境変数を分割して各ディレクトリでコマンドを検索
static char	*search_in_path(const char *cmd, const char *path_env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		perror_exit("malloc");

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

// cmd : ls || /bin/ls
char	*search_external_path(const char *cmd, t_env **env_lst)
{
	char	*path_env;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strcmp(cmd, ".") == 0)
	{
		write(STDERR_FILENO, "minishell: .: filename argument required\n", 42);
		write(STDERR_FILENO, ".: usage: . filename [arguments]\n", 33);
		exit(EXIT_BUILTIN_MISUSE);
	}
	if (ft_strchr(cmd, '/'))
			return (ft_strdup(cmd));
	// コマンド名のみの場合、PATHを検索
	path_env = *ft_get_env(*env_lst, "PATH");
	return (search_in_path(cmd, path_env));
}
