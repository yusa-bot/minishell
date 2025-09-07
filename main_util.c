/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:23:24 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/07 20:35:34 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin_name(const char *name)
{
    if (!name) return 0;
    return (!ft_strcmp(name, "echo")
         || !ft_strcmp(name, "cd")
         || !ft_strcmp(name, "pwd")
         || !ft_strcmp(name, "export")
         || !ft_strcmp(name, "unset")
         || !ft_strcmp(name, "env")
         || !ft_strcmp(name, "exit"));
}

int must_run_in_parent(const char *name)
{
    return (!ft_strcmp(name, "cd")
         || !ft_strcmp(name, "export")
         || !ft_strcmp(name, "unset")
         || !ft_strcmp(name, "exit"));
}



// echo/cd/pwd/export/unset/env/exit へディスパッチして終了コードを返す
int run_builtin(const char *name, char **argv, t_env **env)
{
	int status;

	status = 0;
	if (ft_strcmp(name, "echo") == 0)
		status = builtin_echo(argv);
	else if (ft_strcmp(name, "cd") == 0)
		status = builtin_cd(argv, env);
	else if (ft_strcmp(name, "pwd") == 0)
		status = builtin_pwd();
	else if (ft_strcmp(name, "export") == 0)
		status = builtin_export(argv, env);
	else if (ft_strcmp(name, "unset") == 0)
		status = builtin_unset(argv, env);
	else if (ft_strcmp(name, "env") == 0)
		status = builtin_env(*env);
	else if (ft_strcmp(name, "exit") == 0)
		status = builtin_exit(argv);
	set_last_status(status);
	return status;
}

// exec_path.c（外部コマンド解決）
char *resolve_exec_path(const char *name, t_env *env)
{
	char *path;

	path = get_env_var("PATH", env);
	if (!path)
		return NULL;
	return find_executable(name, path);
}
