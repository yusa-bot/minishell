/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_external_saerch_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:45:01 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 21:37:58 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	if (!temp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

// PATH環境変数を分割して各ディレクトリでコマンドを検索
static char	*search_in_path(const char *cmd, const char *path_env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!path_env)
	{
		write(STDERR_FILENO, "minishell: command not found\n", 29);
		exit(EXIT_CMD_NOT_FOUND);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
	free(paths[i++]);
	free(paths);
	if (errno == EACCES)
	{
		perror(cmd);
		exit(EXIT_NO_EXEC);
	}
	else
	{
		perror(cmd);
		exit(EXIT_CMD_NOT_FOUND);
	}
	return (NULL);
}

char	*search_external_path(const char *cmd, t_env **env)
{
	char	*path_env;
	char	*result;
	char	*cwd;

	if (!cmd || !*cmd)
	{
		write(STDERR_FILENO, "minishell: command not found\n", 29);
		exit(EXIT_CMD_NOT_FOUND);
	}
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		if (errno == EACCES)
		{
			perror(cmd);
			exit(EXIT_NO_EXEC);
		}
		else
		{
			perror(cmd);
			exit(EXIT_CMD_NOT_FOUND);
		}
	}
	if (ft_strchr(cmd, '/'))// 相対パス
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			cwd = ft_get_env(*env, "PWD");
		result = build_full_path(cwd, cmd);//cwd+cmd
		free(cwd);
		if (result && access(result, X_OK) == 0)
			return (result);
		free(result);
		if (errno == EACCES)
		{
			perror(cmd);
			exit(EXIT_NO_EXEC);
		}
		else
		{
			perror(cmd);
			exit(EXIT_CMD_NOT_FOUND);
		}
	}
	// コマンド名のみの場合、PATHを検索
	path_env = ft_get_env(*env, "PATH");
	return (search_in_path(cmd, path_env));
}
