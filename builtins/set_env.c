/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:29:18 by rinka             #+#    #+#             */
/*   Updated: 2025/08/24 12:05:13 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *set_env(char **envp)
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
			ft_envlst_clear(&lst);
			return (NULL);
		}
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (value == NULL)
		{
			free (key);
			ft_envlst_clear(&lst);
			return (NULL);
		}
		ft_envlst_add_back(&lst,ft_envlst_new(key, value, 1));//初期はすべてexportなのでflagたてる
		i++;
	}
	return (lst);
}


// // void	ft_add_export(t_env *env_lst, char)
// #include <fcntl.h>

// int main(int argc, char **argv, char **envp)//"export TEST=/test/pathでテスト"
// {
// 	t_env *env_lst;
// 	(void)argc;

// 	env_lst = NULL;
// 	env_lst = set_env(envp);

// 	int env_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (env_fd == -1)
// 	{
// 		return (1);
// 	}

// 	//export TEST=/test/path
// 	ft_add_env(&env_lst, "TEST=/test/path", 1);
// 	//export TEST2=/test2/path
// 	ft_add_env(&env_lst, "TEST2=/test2/path", 0);

// 	//unset前
// 	ft_put_envs(env_lst, env_fd);//順番？？
// 	write(env_fd, "\n", 1);
// 	ft_put_exports(env_lst, env_fd);
// 	write(env_fd, "\n", 1);

// 	int unset_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (unset_fd == -1)
// 	{
// 		return (1);
// 	}

// 		//TEST=/test/pathをunset
// 	ft_unset(&env_lst, "TEST");

// 	//unset後
// 	ft_put_envs(env_lst, unset_fd);
// 	write(unset_fd, "\n", 1);
// 	ft_put_exports(env_lst, unset_fd);

// 	//t_envのfree
// 	ft_envlst_clear(&env_lst);
// }
