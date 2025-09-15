/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:29:18 by rinka             #+#    #+#             */
/*   Updated: 2025/09/15 13:30:35 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// minishellで動的に追加/変更した環境変数の取得用
char *ft_get_env(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return env->value;
		env = env->next;
	}
	return NULL;
}

t_env *ft_set_env(char **envp)
{
	t_env *lst;
	int	i;
	char *key;
	char *value;

	lst = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		if (key == NULL)
		{
			ft_lst_clear(&lst);
			return (NULL);
		}
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (value == NULL)
		{
			free (key);
			ft_lst_clear(&lst);
			return (NULL);
		}
		ft_lst_add_back(&lst, ft_lst_new(key, value, 1)); //初期はすべてexportなのでflagたてる
		i++;
	}
	return (lst);
}

void ft_add_env(t_env **env_lst, char *str, int is_export)
{
	char *key;
	char *value;
	char *equal_pos;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos == NULL)// "export TEST" の場合（=がない）
	{
		key = ft_strdup(str);
		value = NULL;
	}
	else// "export TEST=value" の場合（=がある）
	{
		key = ft_strndup(str, equal_pos - str);
		value = ft_strdup(equal_pos + 1);
	}
	if (key == NULL || (equal_pos != NULL && value == NULL))
	{
		free(key);
		free(value);
		ft_lst_clear(env_lst);
		return; // error_exit?
	}
	if (*env_lst == NULL)
		*env_lst = ft_lst_new(key, value, is_export);
	else
		ft_lst_add_front(env_lst, ft_lst_new(key, value, is_export));
}


// #include <fcntl.h>
//int main(int argc, char **argv, char **envp) // export TEST=/test/pathでテスト
//{
//	(void)argc;
//	t_env *env_lst;

//	env_lst = ft_set_env(envp);

//	int env_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (env_fd == -1)
//		return (1);

//	// export TEST=/test/path
//	ft_add_env(&env_lst, "TEST=/test/path", 1);
//	// export TEST2=/test2/path
//	ft_add_env(&env_lst, "TEST2=/test2/path", 0);

//	// unset前
//	ft_env(env_lst, env_fd);
//	write(env_fd, "\n", 1);
//	ft_export(env_lst, env_fd);
//	write(env_fd, "\n", 1);

//	int unset_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (unset_fd == -1)
//		return (1);

//	// TEST=/test/pathをunset
//	ft_unset(&env_lst, "TEST");

//	// unset後
//	ft_env(env_lst, unset_fd);
//	write(unset_fd, "\n", 1);
//	ft_export(env_lst, unset_fd);

//	ft_lst_clear(&env_lst);
//}

